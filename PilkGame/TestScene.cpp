#include <SceneManager.h>
#include <ResourceManager.h>

#include "TestScene.h"

#include <glad.h>
#include <glfw3.h>
#include <Camera.h>
#include <SystemManager.h>
#include <EntityManager.h>
#include <SpriteManager.h>
#include <Entity.h>
#include <System.h>

// TEMP VARS ----------------------------------

	//ComponentTransform* trans1 = new ComponentTransform(glm::vec2(0.0f, 0.0f), 0.0f, glm::vec2(1.0f, 1.0f), 0.9f);
	//ComponentSprite* sprite1 = new ComponentSprite("resources/textures/grass.png");
	//ComponentShader* shader1 = new ComponentShader("resources/shaders/VertexShader.vert", "resources/shaders/FragmentShader.frag");

	//ComponentTransform* trans2 = new ComponentTransform(glm::vec2(0.0f, 0.0f), 0.0f, glm::vec2(1.0f, 1.0f), 1.0f);
	//ComponentSprite* sprite2 = new ComponentSprite("resources/textures/capsule.jpg");
	//ComponentShader* shader2 = new ComponentShader("resources/shaders/VertexShader.vert", "resources/shaders/FragmentShader.frag");

	//						POS							  TARGET
Camera mCamera = Camera(glm::vec3(0.0f, 0.0f, -1.0f), glm::vec3(0.0f, 0.0f, 1.0f));

// TEMP VARS ----------------------------------

SystemManager* sysman = new SystemManager();
EntityManager* entitymanager = new EntityManager();

SystemRender* sysrender = new SystemRender(&mCamera);
SystemPhysics* sysphys = new SystemPhysics();

ComponentPhysics* playerphys;

TestScene::TestScene() : Scene()
{
	mSceneManagerInstance->WindowName = "tom smells!";
}

TestScene::~TestScene() 
{
	this->Close();
}

void TestScene::Load() 
{
	/*
	sysman->AddSystem(sysrender);
	sysman->AddSystem(sysphys);

	Entity* e = new Entity("randy");
	ComponentTransform* randytrans = new ComponentTransform(glm::vec2(0.0f, 0.0f), 0.0f, glm::vec2(0.5f, 0.5f), 1.1f);
	ComponentSprite* randysprite = new ComponentSprite("resources/textures/capsule.jpg");
	ComponentShader* randyshader = new ComponentShader("resources/shaders/VertexShader.vert", "resources/shaders/FragmentShader.frag");
	playerphys = new ComponentPhysics();
	e->AddComponent(randytrans);
	e->AddComponent(randysprite);
	e->AddComponent(randyshader);
	e->AddComponent(playerphys);

	entitymanager->AddEntity(e);

	SpriteManager::InitSpriteGeometry();
	*/
}

void TestScene::Render() const
{

}

void TestScene::Update() 
{
	mCamera.UpdateCamera();

	sysman->ExecuteSystems(entitymanager->mEntities);
}

void TestScene::Close() 
{


}

void TestScene::ProcessKeyboardInput(GLFWwindow* pWindow, int pKey, int pScancode, int pAction, int pMods) 
{
	if (pKey == GLFW_KEY_W && pAction == GLFW_PRESS)
	{
		playerphys->mVelocity.y = 1.0;
	}
	else if (pKey == GLFW_KEY_S && pAction == GLFW_PRESS)
	{
		playerphys->mVelocity.y = -1.0;
	}
	else
	{
		playerphys->mVelocity.y = 0.0;
	}

	if (pKey == GLFW_KEY_A && pAction == GLFW_PRESS)
	{
		playerphys->mVelocity.x = -1.0;
	}
	else if (pKey == GLFW_KEY_D && pAction == GLFW_PRESS)
	{
		playerphys->mVelocity.x = 1.0;
	}
	else
	{
		playerphys->mVelocity.x = 0.0;
	}

# pragma region cameraControloids
	if (pKey == GLFW_KEY_G && pAction == GLFW_PRESS)
	{
		Scene* newScene = new TestScene();
		SceneManager::ChangeScene(newScene);
	}

	if (pKey == GLFW_KEY_RIGHT && (pAction == GLFW_REPEAT || pAction == GLFW_PRESS))
	{
		mCamera.MoveCamera(RIGHT, 1.0f);
	}

	if (pKey == GLFW_KEY_LEFT && (pAction == GLFW_REPEAT || pAction == GLFW_PRESS))
	{
		mCamera.MoveCamera(LEFT, 1.0f);
	}

	if (pKey == GLFW_KEY_UP && (pAction == GLFW_REPEAT || pAction == GLFW_PRESS))
	{
		mCamera.MoveCamera(UP, 1.0f);
	}

	if (pKey == GLFW_KEY_DOWN && (pAction == GLFW_REPEAT || pAction == GLFW_PRESS))
	{
		mCamera.MoveCamera(DOWN, 1.0f);
	}

	if (pKey == GLFW_KEY_E && (pAction == GLFW_REPEAT || pAction == GLFW_PRESS))
	{
		mCamera.MoveCamera(ZOOM_IN, 0.1f);
	}

	if (pKey == GLFW_KEY_Q && (pAction == GLFW_REPEAT || pAction == GLFW_PRESS))
	{
		mCamera.MoveCamera(ZOOM_OUT, 0.1f);
	}

	if (pKey == GLFW_KEY_X && pAction == GLFW_PRESS)
	{
		mCamera.ResetZoom();
	}

#pragma endregion
}

void TestScene::ProcessMouseInput(GLFWwindow* pWindow, double pXPos, double pYPos) 
{

}