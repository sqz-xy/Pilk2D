#include "Entity.h"
#include "Component.h"

Entity::Entity(const std::string pName) : mName(pName), mID(ENTITY_ID++)
{

}

Entity::Entity(const Entity& pEntity) : mName(pEntity.mName), mID(pEntity.mID), mComponents(pEntity.mComponents)
{

}

void Entity::AddComponent(Component* pComponent) {
	mComponents.push_back(pComponent);
}

Entity::~Entity()
{
	for (Component* component : mComponents)
	{
		delete component;
		component = nullptr;
	}

	mComponents.clear();
}
