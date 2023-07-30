#include "ImGUIManager.h"

ImGUIManager* ImGUIManager::mInstance = nullptr;

ImGUIManager::ImGUIManager()
{
}

ImGUIManager::~ImGUIManager()
{
}

ImGUIManager* ImGUIManager::GetInstance()
{
	if (mInstance == nullptr)
	{
		mInstance = new ImGUIManager();
	}

	return mInstance;
}

void ImGUIManager::KillInstance()
{
	if (mInstance != nullptr)
	{
		delete mInstance;
	}
}


