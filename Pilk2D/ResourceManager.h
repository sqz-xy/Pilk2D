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
	ResourceManager(ResourceManager& pOther) = delete;
	void operator=(const ResourceManager& pRhs) = delete;
	
	static ResourceManager* GetInstance();
	static void KillInstance();
	static bool CreateShaderProgram(unsigned int* pProgramHandle, const std::string& pVertFileName, const std::string& pFragFileName);
	static unsigned int LoadTexture(const std::string& pPath);
	static void DeleteResources();

	std::map<std::string, unsigned int> mShaderMap;
	std::map<std::string, unsigned int> mTextureMap;

protected:
	ResourceManager();
	~ResourceManager();

	bool LoadShader(const std::string& pFileName, std::string& pShaderSource);
	bool CompileShader(const GLenum& pShaderType, const std::string& pFileName, unsigned int* pShaderBuffer, int* pSuccess, char* pInfoLog);

	static ResourceManager* mInstance;

};

