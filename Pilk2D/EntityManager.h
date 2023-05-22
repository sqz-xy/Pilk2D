
#pragma once

#include <vector>
#include <string>

class SystemManager;
class Entity;

/// Original Author: Thomas Beet, modified by Piotr
/// <summary>
/// Entity Manager and its declarations
/// </summary>
class EntityManager final
{
public:
	explicit EntityManager() {};
	~EntityManager() {};

	bool AddEntity(Entity* pEntity);
	bool RemoveEntity(const int pID);
	bool RemoveEntity(const std::string& pName);
	void RemoveEntities(const std::string& pName);
	void ClearEntities();

	Entity* FindEntity(const int pID) const;
	Entity* FindEntity(const std::string& pName) const;
	std::vector<Entity*> FindEntities(const std::string& pName) const;

	inline int EntityCount() const;

	std::vector<Entity*> mEntities;
private:
};

