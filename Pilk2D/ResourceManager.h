#pragma once

#include <glad.h>
#include <string>
#include <map>

const int max_shaders = 20;

/// Original Author: Thomas Beet
/// <summary>
/// Static resource manager, allows loading of shaders, textures and models. Keeps track of them
/// </summary>
class ResourceManager final
{
public:
	static bool CreateShaderProgram(unsigned int* pProgramHandle, const std::string& pVertFileName, const std::string& pFragFileName);
	static unsigned int LoadTexture(const std::string& pPath);
	static void DeleteResources();

private:
	ResourceManager() = delete;
	~ResourceManager() = delete;

	static bool LoadShader(const std::string& pFileName, std::string& pShaderSource);
	static bool CompileShader(const GLenum& pShaderType, const std::string& pFileName, unsigned int* pShaderBuffer, int* pSuccess, char* pInfoLog);
	
	static std::map<std::string, unsigned int> mShaderMap;
	static std::map<std::string, unsigned int> mTextureMap;
};