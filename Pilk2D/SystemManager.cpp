#include "System.h"
#include "vector"
#include "SystemManager.h"
#include "SceneManager.h"
#include "Entity.h"

SystemManager::SystemManager() 
{
	mSceneManagerInstance = SceneManager::GetInstance();
}

SystemManager::~SystemManager() 
{
	ClearSystems();
}

void SystemManager::ExecuteSystems(std::vector<Entity*>pEntities) 
{

	for (System* s : mSystems)
	{
		s->Execute(mSceneManagerInstance->DeltaTime, pEntities);
	}

}

void SystemManager::AddSystem(System* pSystem) 
{
	mSystems.push_back(pSystem);
}

void SystemManager::ClearSystems() 
{	
	for (auto* system : mSystems)
		delete system;

	mSystems.clear();
}