#pragma once
#include "System.h"
#include "vector"

class Entity;

class SystemManager {

public:

	SystemManager();
	~SystemManager();

	void ExecuteSystems(std::vector<Entity*>pEntities);
	void AddSystem(System* pSystems);
	void ClearSystems();

private:

	std::vector<System*>mSystems;

};
