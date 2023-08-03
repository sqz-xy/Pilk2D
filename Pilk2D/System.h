#pragma once

#include "Component.h"
#include "vector"

class Camera;
class Entity;

class System {

public:

	System();
	~System();

	virtual void Execute(const float pDeltaTime, std::vector<Entity*> pEntities);

	// think of some optimisation

private:
};

class SystemRender : public System {

public: 

	SystemRender(Camera* pCamera);
	~SystemRender();

	void Execute(const float pDeltaTime, std::vector<Entity*> pEntities) override;

private:

	void Render(ComponentSprite* pSprite, ComponentTransform* pTrans, ComponentShader* pShader);

	Camera* mCamera;

};

class SystemPhysics : public System {
public:

	SystemPhysics();
	~SystemPhysics();

	void Execute(const float pDeltaTime, std::vector<Entity*> pEntities) override;

private:


	void TomSmells(ComponentPhysics* pFizzicks, ComponentTransform* pTrans, const float pdeltoid);
};

class SystemCollisionAABB : public System {
public:

private:

};