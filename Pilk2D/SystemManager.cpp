#pragma once
#include "System.h"
#include "vector"
#include "SystemManager.h"
#include "SceneManager.h"
#include "Entity.h"

SystemManager::SystemManager() {
}

SystemManager::~SystemManager() {
	ClearSystems();
}

void SystemManager::ExecuteSystems(std::vector<Entity*>pEntities) {

	for (System* s : mSystems)
	{
		s->Execute(SceneManager::DeltaTime, pEntities);
	}

}

void SystemManager::AddSystem(System* pSystem) {
	mSystems.push_back(pSystem);
}

void SystemManager::ClearSystems() {
	mSystems.clear();
}