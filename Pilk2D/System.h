#pragma once

#include "Camera.h"
#include "Entity.h"
#include "Component.h"
#include "vector"

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