
#include "EntityManager.h"
#include "Entity.h"
#include "Debug.h"
#include <iostream>

/// <summary>
/// Adds an entity to the entity list
/// </summary>
/// <param name="pEntity">Entity to add</param>
/// <returns>Success</returns>
bool EntityManager::AddEntity(Entity* pEntity)
{
	// Cant be null
	if (pEntity == nullptr)
		return false;

	// If there are no entities, no need for an ID check
	if (mEntities.empty())
	{
		mEntities.push_back(pEntity);
		return true;
	}

	// Entities cant have the same IDs
	for (int i = 0; i < mEntities.size(); i++)
	{
		if (mEntities[i]->GetID() == pEntity->GetID())
		{
			std::cerr << "Can't have multiple entities with the same ID";
			return false;
		}

		mEntities.push_back(pEntity);
		return true;
	}
}

/// <summary>
/// Removes an entity based on ID
/// </summary>
/// <param name="pID">Entity ID to remove</param>
/// <returns>success</returns>
bool EntityManager::RemoveEntity(const int pID)
{
	for (int i = 0; i < mEntities.size(); i++)
	{
		if (mEntities[i]->GetID() == pID)
		{
			delete mEntities[i];
			mEntities.erase(mEntities.begin() + i);
			return true;
			PRINT_DEBUG("Entity Removed");
		}
	}
	return false;
}

/// <summary>
/// Removes an entity based on name
/// </summary>
/// <param name="pName">Entity name to remove</param>
/// <returns>Success</returns>
bool EntityManager::RemoveEntity(const std::string& pName)
{
	for (int i = 0; i < mEntities.size(); i++)
	{
		if (mEntities[i]->GetName() == pName)
		{
			delete mEntities[i];
			mEntities.erase(mEntities.begin() + i);
			return true;
			PRINT_DEBUG("Entity Removed");
		}
	}
	return false;
}

/// <summary>
/// Removes entities based on name
/// </summary>
/// <param name="pName">Name to remove</param>
void EntityManager::RemoveEntities(const std::string& pName)
{
	for (int i = 0; i < mEntities.size(); i++)
	{
		if (mEntities[i]->GetName() == pName)
		{
			delete mEntities[i];
			mEntities.erase(mEntities.begin() + i);
		}
	}
}

/// <summary>
/// Finds entity based on ID
/// </summary>
/// <param name="pID">Entity ID to find</param>
/// <returns>Entity</returns>
Entity* EntityManager::FindEntity(const int pID) const
{
	for (int i = 0; i < mEntities.size(); i++)
	{
		if (mEntities[i]->GetID() == pID)
		{
			return mEntities[i];
		}
	}
	return nullptr;
}

/// <summary>
/// Finds entity based on Name
/// </summary>
/// <param name="pID">Entity Name to find</param>
/// <returns>Entity</returns>
Entity* EntityManager::FindEntity(const std::string& pName) const
{
	for (int i = 0; i < mEntities.size(); i++)
	{
		if (mEntities[i]->GetName() == pName)
		{
			return mEntities[i];
		}
	}
	return nullptr;
}

/// <summary>
/// Clears all entiti
/// </summary>
void EntityManager::ClearEntities()
{
	for (auto* entity : mEntities)
		delete entity;

	mEntities.clear();
	PRINT_DEBUG("Entities Cleared");
}

/// <summary>
/// Finds all entities with a given name
/// </summary>
/// <param name="pName">Name to find</param>
/// <returns>Vector of entities</returns>
std::vector<Entity*> EntityManager::FindEntities(const std::string& pName) const
{
	std::vector<Entity*> entities;
	for (int i = 0; i < mEntities.size(); i++)
	{
		if (mEntities[i]->GetName() == pName)
		{
			entities.push_back(mEntities[i]);
		}
	}
	return entities;
}

/// <summary>
/// Entity count
/// </summary>
/// <returns>Number of entities</returns>
inline int EntityManager::EntityCount() const
{
    return mEntities.size();
}

