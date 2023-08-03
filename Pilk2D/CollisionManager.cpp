#include "CollisionManager.h"

CollisionManager::CollisionManager()
{
	
}

CollisionManager::~CollisionManager()
{
	ClearManifold();
}

void CollisionManager::RegisterCollision(Entity* pEntity1, Entity* pEntity2, CollisionType pType)
{
	for (Collision* col : mCollisionManifold)
	{
		if (col->entity1 == pEntity1 && col->entity1 == pEntity2)
			return;
	}

	Collision* col = new Collision();
	col->entity1 = pEntity1;
	col->entity2 = pEntity2;
	col->type = pType;

	mCollisionManifold.push_back(col);
}

void CollisionManager::ProcessCollisions()
{

}

void CollisionManager::ClearManifold()
{
	mCollisionManifold.clear();
}