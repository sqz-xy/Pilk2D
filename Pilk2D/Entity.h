#pragma once

#include <string>
#include <vector>

class Component;

static unsigned int ENTITY_ID = 0;

class Entity
{
public:
	Entity(const std::string& pName);
	Entity(const Entity& pEntity);
	~Entity();

	template<typename T> T* GetComponent();
	inline const std::string& Name();
	inline const unsigned int ID();

	Entity& operator= (const class Entity&) = default;

private:
	const std::string& mName;
	const unsigned int mID;
	std::vector<Component*> mComponents; // Heap Allocation for components
};