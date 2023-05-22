#include "Entity.h"
#include "Component.h"

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
