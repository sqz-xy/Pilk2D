#pragma once

#include "ResourceManager.h"

#include <iostream>
#include <fstream>
#include <vector>
#include <stb_image.h>

ResourceManager* ResourceManager::mInstance = nullptr;

ResourceManager::ResourceManager()
{
}

ResourceManager::~ResourceManager()
{
}

/// Original Author: Thomas Beet
/// <summary>
/// Loads string data for a shader file
/// </summary>
/// <param name="p_fileName">path for the shader file</param>
/// <param name="p_shaderSource">string source to store the shader</param>
/// <returns>bool - success</returns>
bool ResourceManager::LoadShader(const std::string& pFileName, std::string& pShaderSource)
{
	pShaderSource.clear();
	std::ifstream shader(pFileName);

	if (shader)
	{
		char ch;
		while (shader.get(ch))
		{
			pShaderSource += ch;
		}
		return true;
	}
	return false;
}

/// Original Author: Thomas Beet
/// <summary>
/// Compiles a shader 
/// </summary>
/// <param name="p_shaderType">Type of shader</param>
/// <param name="p_fileName">File path for the shader</param>
/// <param name="p_shaderBuffer">Buffer int for shader</param>
/// <param name="p_success">return code</param>
/// <param name="p_infoLog">information on shader compilation</param>
/// <returns>bool - success</returns>
bool ResourceManager::CompileShader(const GLenum& pShaderType, const std::string& pFileName, unsigned int* pShaderBuffer, int* pSuccess, char* pInfoLog)
{
	std::string shaderSourceString;
	const char* shaderSource;

	if (!LoadShader(pFileName, shaderSourceString))
	{
		std::cout << pShaderType << " File not loaded" << std::endl;
		return false;
	}

	shaderSource = shaderSourceString.c_str();
	*pShaderBuffer = glCreateShader(pShaderType);
	glShaderSource(*pShaderBuffer, 1, &shaderSource, NULL);
	glCompileShader(*pShaderBuffer);

	glGetShaderiv(*pShaderBuffer, GL_COMPILE_STATUS, pSuccess);
	if (!pSuccess)
	{
		glGetShaderInfoLog(*pShaderBuffer, 512, NULL, pInfoLog);
		std::cout << pShaderType << "shader compilation error " << std::endl << pInfoLog << std::endl;
		return false;
	}
	return true;
}

ResourceManager* ResourceManager::GetInstance()
{
	if (mInstance == nullptr)
	{
		mInstance = new ResourceManager();
	}

	return mInstance;
}

void ResourceManager::KillInstance()
{
	if (mInstance != nullptr)
	{
		delete mInstance;
	}
}

/// Original Author: Thomas Beet
/// <summary>
/// Creates a shader program using the passed in shader paths
/// </summary>
/// <param name="p_sProgram">int to hold the program ID</param>
/// <param name="p_vertFileName">vertex shader file path</param>
/// <param name="p_fragFileName">fragment shader file path</param>
/// <returns></returns>
bool ResourceManager::CreateShaderProgram(unsigned int* pProgramHandle, const std::string& pVertFileName, const std::string& pFragFileName)
{
	ResourceManager* ResourceManager = GetInstance();

	// Shader signature is the vertex + fragment filenames appended
	// Preallocate buffer to store shader signature

	const int returnBufferSize = 512;
	char* shaderSig = new char [returnBufferSize];

	strcpy_s(shaderSig, returnBufferSize, pVertFileName.c_str());
	strcat_s(shaderSig, returnBufferSize, pFragFileName.c_str());
	
	// If the shader already exists, return its program id
	const std::size_t shaderCount = ResourceManager->mShaderMap.count(shaderSig), shaderLimit = 1;
	if (shaderCount == shaderLimit)
	{
		*pProgramHandle = ResourceManager->mShaderMap.at(shaderSig);
		return true;
	}

	int success;
	char infoLog[returnBufferSize];

	unsigned int vertexShader, fragmentShader;

	// Compile and attach shaders
	ResourceManager->CompileShader(GL_VERTEX_SHADER, pVertFileName.c_str(), &vertexShader, &success, infoLog);
	ResourceManager->CompileShader(GL_FRAGMENT_SHADER, pFragFileName.c_str(), &fragmentShader, &success, infoLog);

	*pProgramHandle = glCreateProgram();

	glAttachShader(*pProgramHandle, vertexShader);
	glAttachShader(*pProgramHandle, fragmentShader);
	glLinkProgram(*pProgramHandle);

	glGetProgramiv(*pProgramHandle, GL_LINK_STATUS, &success);
	if (!success)
	{
		glGetProgramInfoLog(*pProgramHandle, returnBufferSize, NULL, infoLog);
		std::cout << "Shader program attachment error " << std::endl << infoLog << std::endl;
		return false;
	}

	// Add the shader to the map
	ResourceManager->mShaderMap.insert(std::pair <std::string, unsigned int > (shaderSig, *pProgramHandle));
	delete[] shaderSig;

	return true;
}

/// By Thomas Beet, Code written using help from https://learnopengl.com/Getting-started/Textures 
/// <summary>
/// Loads a texture using STBI
/// </summary>
/// <param name="p_path">Texture path</param>
/// <param name="p_directory">Texture directory</param>
/// <returns>Texture buffer</returns>
unsigned int ResourceManager::LoadTexture(const std::string& pPath)
{
	ResourceManager* ResourceManager = GetInstance();

	const std::size_t texCount = ResourceManager->mTextureMap.count(pPath), texLimit = 1;
	if (texCount == texLimit)
	{
		unsigned int texBuffer = ResourceManager->mTextureMap.at(pPath);
		return texBuffer;
	}

	// Currently only loads one texture
	unsigned int texture1;

	glGenTextures(1, &texture1);
	glBindTexture(GL_TEXTURE_2D, texture1);
	// set the texture wrapping parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	// set texture wrapping to GL_REPEAT (default wrapping method)
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	// set texture filtering parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	// load image, create texture and generate mipmaps
	int width, height, nrChannels;
	stbi_set_flip_vertically_on_load(true); // tell stb_image.h to flip loaded texture's on the y-axis.
	// The FileSystem::getPath(...) is part of the GitHub repository so we can find files on any IDE/platform; replace it with your own image path.
	unsigned char* data = stbi_load(pPath.c_str(), &width, &height, &nrChannels, 0);
	if (data)
	{
		GLenum format{};
		if (nrChannels == 1)
			format = GL_RED;
		else if (nrChannels == 3)
			format = GL_RGB;
		else if (nrChannels == 4)
			format = GL_RGBA;

		glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		std::cout << "Failed to load texture" << std::endl;
	}
	stbi_image_free(data);
	
	ResourceManager->mShaderMap.insert(std::pair <std::string, unsigned int >(pPath, texture1));
	return texture1;
}

/// By Thomas Beet
/// <summary>
/// Delete stored resources
/// </summary>
void ResourceManager::DeleteResources()
{
	ResourceManager* ResourceManager = GetInstance();

	for (const auto& shader : ResourceManager->mShaderMap)
	{
		glDeleteProgram(shader.second);
	}
	ResourceManager->mShaderMap.clear();

	// Could be an isue
	if (ResourceManager->mTextureMap.size() > 0)
	{
		std::vector<GLuint> texIDs;

		for (const auto& texture : ResourceManager->mTextureMap)
		{
			texIDs.push_back(static_cast<GLuint>(texture.second));
		}
		glDeleteTextures(texIDs.size(), &texIDs[0]);

		ResourceManager->mTextureMap.clear();
	}

}
