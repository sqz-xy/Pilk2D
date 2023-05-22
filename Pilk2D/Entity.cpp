#include "Entity.h"
#include "Debug.h"

// TODO: COMPONENT_H

Entity::Entity(const std::string& pName) : mName(pName), mID(ENTITY_ID++)
{

}

Entity::Entity(const Entity& pEntity) : mName(pEntity.mName), mID(pEntity.mID), mComponents(pEntity.mComponents)
{

}

Entity::~Entity()
{
	//for (Component* component : mComponents)
	// TODO: Delete Components	
}

template<typename T> T* Entity::GetComponent()
{
	for (int i = 0; i < mComponents.size(); i++)
	{
		T* result = dynamic_cast<T*>(mComponents[i]);
		if (result != nullptr)
		{
			return result;
		}
	}
	return nullptr;
}

inline const std::string& Entity::GetName()
{
	return mName;
}

inline const unsigned int Entity::GetID()
{
	return mID;
}
