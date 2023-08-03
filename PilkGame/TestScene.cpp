#include <SceneManager.h>
#include <ResourceManager.h>
#include <ImGUIManager.h>

#include "TestScene.h"

#include <glad.h>
#include <glfw3.h>
#include <Camera.h>
#include <SystemManager.h>
#include <EntityManager.h>
#include <SpriteManager.h>
#include <Entity.h>
#include <System.h>
#include <imgui.h>


Camera* mCamera; 
SystemManager* sysman; 
EntityManager* entitymanager;
SystemRender* sysrender;
SystemPhysics* sysphys;
ComponentPhysics* playerphys;
ImGUIManager* GUIManager;

TestScene::TestScene() : Scene()
{
	mSceneManagerInstance->WindowName = "tom smells!";
}

TestScene::~TestScene() 
{

}

void TestScene::Load() 
{
	mCamera = new Camera(glm::vec3(0.0f, 0.0f, -1.0f), glm::vec3(0.0f, 0.0f, 1.0f));
	sysman = new SystemManager();
	entitymanager = new EntityManager();
	sysrender = new SystemRender(mCamera);
	sysphys = new SystemPhysics();
	playerphys = new ComponentPhysics();
	GUIManager = ImGUIManager::GetInstance();

	sysman->AddSystem(sysrender);
	sysman->AddSystem(sysphys);

	Entity* enemy = new Entity("badrandy");
#pragma region enemy
	ComponentTransform* badrandytrans = new ComponentTransform(glm::vec2(1.0f, 0.0f), 0.0f, glm::vec2(0.5f, 0.5f), 1.0f);
	ComponentSprite* badrandysprite = new ComponentSprite("resources/textures/capsule.jpg");
	ComponentShader* badrandyshader = new ComponentShader("resources/shaders/VertexShader.vert", "resources/shaders/FragmentShader.frag");
	ComponentCollisionAABB* badrandycol = new ComponentCollisionAABB(0.5f, 0.5f);
	enemy->AddComponent(badrandytrans);
	enemy->AddComponent(badrandysprite);
	enemy->AddComponent(badrandyshader);
	enemy->AddComponent(badrandycol);
#pragma endregion

	Entity* e = new Entity("randy");
	ComponentTransform* randytrans = new ComponentTransform(glm::vec2(0.0f, 0.0f), 0.0f, glm::vec2(0.5f, 0.5f), 1.1f);
	ComponentSprite* randysprite = new ComponentSprite("resources/textures/sprite_sheet.png");
	ComponentShader* randyshader = new ComponentShader("resources/shaders/VertexShader.vert", "resources/shaders/FragmentShader.frag");
	ComponentCollisionAABB* randycol = new ComponentCollisionAABB(0.5f, 0.5f);
	playerphys = new ComponentPhysics();
	e->AddComponent(randytrans);
	e->AddComponent(randysprite);
	e->AddComponent(randyshader);
	e->AddComponent(randycol);
	e->AddComponent(playerphys);

	entitymanager->AddEntity(e);
	entitymanager->AddEntity(enemy);
}

void TestScene::Render() const
{

}

void TestScene::Update() 
{
	mCamera->UpdateCamera();

	sysman->ExecuteSystems(entitymanager->mEntities);
}

void TestScene::RenderGUI()
{
	GUIManager->StartFrame();

	ImGui::ShowDemoWindow();

	GUIManager->EndFrame();
}

void TestScene::Close() 
{
	entitymanager->ClearEntities();
	sysman->ClearSystems();

	delete entitymanager;
	entitymanager = nullptr;

	delete sysman;
	sysman = nullptr;

	delete mCamera;
	mCamera = nullptr;
}

void TestScene::ProcessKeyboardInput(GLFWwindow* pWindow, int pKey, int pScancode, int pAction, int pMods) 
{
	if (glfwGetKey(pWindow, GLFW_KEY_W) == GLFW_PRESS)
	{
		playerphys->mVelocity.y = 1.0f;
	}
	else if (glfwGetKey(pWindow, GLFW_KEY_S) == GLFW_PRESS)
	{
		playerphys->mVelocity.y = -1.0f;
	}
	else
	{
		playerphys->mVelocity.y = 0.0f;
	}

	if (glfwGetKey(pWindow, GLFW_KEY_A) == GLFW_PRESS)
	{
		playerphys->mVelocity.x = -1.0f;
	}
	else if (glfwGetKey(pWindow, GLFW_KEY_D) == GLFW_PRESS)
	{
		playerphys->mVelocity.x = 1.0f;
	}
	else
	{
		playerphys->mVelocity.x = 0.0f;
	}

# pragma region cameraControloids
	if (pKey == GLFW_KEY_G && pAction == GLFW_PRESS)
	{
		SceneManager::ChangeScene(new TestScene());
	}

	if (pKey == GLFW_KEY_RIGHT && (pAction == GLFW_REPEAT || pAction == GLFW_PRESS))
	{
		mCamera->MoveCamera(RIGHT, 1.0f);
	}

	if (pKey == GLFW_KEY_LEFT && (pAction == GLFW_REPEAT || pAction == GLFW_PRESS))
	{
		mCamera->MoveCamera(LEFT, 1.0f);
	}

	if (pKey == GLFW_KEY_UP && (pAction == GLFW_REPEAT || pAction == GLFW_PRESS))
	{
		mCamera->MoveCamera(UP, 1.0f);
	}

	if (pKey == GLFW_KEY_DOWN && (pAction == GLFW_REPEAT || pAction == GLFW_PRESS))
	{
		mCamera->MoveCamera(DOWN, 1.0f);
	}

	if (pKey == GLFW_KEY_E && (pAction == GLFW_REPEAT || pAction == GLFW_PRESS))
	{
		mCamera->MoveCamera(ZOOM_IN, 0.1f);
	}

	if (pKey == GLFW_KEY_Q && (pAction == GLFW_REPEAT || pAction == GLFW_PRESS))
	{
		mCamera->MoveCamera(ZOOM_OUT, 0.1f);
	}

	if (pKey == GLFW_KEY_X && pAction == GLFW_PRESS)
	{
		mCamera->ResetZoom();
	}

#pragma endregion
}

void TestScene::ProcessMouseInput(GLFWwindow* pWindow, double pXPos, double pYPos) 
{

}