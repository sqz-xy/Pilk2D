#include "System.h"
#include "Camera.h"

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

}

#pragma endregion