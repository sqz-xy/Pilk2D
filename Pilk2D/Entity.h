#pragma once

#include <string>
#include <vector>

class Component;

static unsigned int ENTITY_ID = 0;

class Entity
{
public:
	Entity(const std::string pName);
	Entity(const Entity& pEntity);
	~Entity();

	template<typename T> T* GetComponent();
	inline const std::string& GetName() { return mName; };
	inline const int GetID() { return mID; };
	void AddComponent(Component* pComponent);

	Entity& operator= (const class Entity&) = default;

private:
	const std::string mName;
	const unsigned int mID;
	std::vector<Component*> mComponents; // Heap Allocation for components
};

template<typename T>
inline T* Entity::GetComponent()
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