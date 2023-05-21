#include "System.h"
#include "Camera.h"
#include "Component.h"
#include "SpriteManager.h"

#pragma region System

System::System() {}

System::~System() {}

void System::Execute(const float pDeltaTime, std::vector<Entity*> pEntities) {
	// does nothing
}

#pragma endregion

#pragma region SystemRender

SystemRender::SystemRender(Camera* pCamera) {
	mCamera = pCamera;
}

SystemRender::~SystemRender() {

}

void SystemRender::Execute(const float pDeltaTime, std::vector<Entity*> pEntities) {

	for (Entity* e : pEntities)
	{
		ComponentSprite* sprite = e->GetComponent<ComponentSprite>();
		ComponentTransform* trans = e->GetComponent<ComponentTransform>();
		ComponentShader* shader = e->GetComponent<ComponentShader>();

		if (sprite != nullptr && trans != nullptr && shader != nullptr)
		{
			Render(sprite, trans, shader);
		}
	}

}

void SystemRender::Render(ComponentSprite* pSprite, ComponentTransform* pTrans, ComponentShader* pShader) {

	pSprite->UseSprite();
	pShader->UseShader(*mCamera, pTrans->mTransform);
	SpriteManager::DrawSpriteGeometry();

}

#pragma endregion