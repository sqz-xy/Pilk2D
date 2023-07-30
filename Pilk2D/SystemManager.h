#pragma once
#include "vector"

class Entity;
class System;
class SceneManager;

class SystemManager {

public:

	SystemManager();
	~SystemManager();

	void ExecuteSystems(std::vector<Entity*>pEntities);
	void AddSystem(System* pSystems);
	void ClearSystems();

private:
	std::vector<System*>mSystems;
	SceneManager* mSceneManagerInstance;
};
