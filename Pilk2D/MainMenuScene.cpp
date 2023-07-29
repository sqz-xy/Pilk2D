//#include "Scene.h"
//#include "SceneManager.h"
//#include "MainMenuScene.h"
//
//#include <glad.h>
//#include <glfw3.h>
//#include "ResourceManager.h"
//
//#include "glm.hpp"
//#include "gtc/matrix_transform.hpp"
//#include "gtc/type_ptr.hpp"
//#include "SpriteManager.h"
//#include "Camera.h"
//#include "Component.h"
//#include "SystemManager.h"
//#include "EntityManager.h"
//
//// 
//
//
//
//
//	// TEMP VARS ----------------------------------
//
//	//ComponentTransform* trans1 = new ComponentTransform(glm::vec2(0.0f, 0.0f), 0.0f, glm::vec2(1.0f, 1.0f), 0.9f);
//	//ComponentSprite* sprite1 = new ComponentSprite("resources/textures/grass.png");
//	//ComponentShader* shader1 = new ComponentShader("resources/shaders/VertexShader.vert", "resources/shaders/FragmentShader.frag");
//
//	//ComponentTransform* trans2 = new ComponentTransform(glm::vec2(0.0f, 0.0f), 0.0f, glm::vec2(1.0f, 1.0f), 1.0f);
//	//ComponentSprite* sprite2 = new ComponentSprite("resources/textures/capsule.jpg");
//	//ComponentShader* shader2 = new ComponentShader("resources/shaders/VertexShader.vert", "resources/shaders/FragmentShader.frag");
//
//	//						POS							  TARGET
//	Camera mCamera = Camera(glm::vec3(0.0f, 0.0f, -1.0f), glm::vec3(0.0f, 0.0f, 1.0f));
//	
//	// TEMP VARS ----------------------------------
//
//	SystemManager* sysman = new SystemManager();
//	EntityManager* entitymanager = new EntityManager();
//
//	SystemRender* sysrender = new SystemRender(&mCamera);
//
//	explicit MainMenuScene::MainMenuScene()
//	{ 
//		SceneManager::WindowName = "Main Menu!";
//	}
//
//	~MainMenuScene::MainMenuScene() override
//	{
//		this->Close();
//	}
//
//	void MainMenuScene::Load() override
//	{
//		sysman->AddSystem(sysrender);
//
//		Entity* e = new Entity("randy");
//		ComponentTransform* randytrans = new ComponentTransform(glm::vec2(0.0f, 0.0f), 0.0f, glm::vec2(1.0f, 0.5f), 1.1f);
//		ComponentSprite* randysprite = new ComponentSprite("resources/textures/capsule.jpg");
//		ComponentShader* randyshader = new ComponentShader("resources/shaders/VertexShader.vert", "resources/shaders/FragmentShader.frag");
//		e->AddComponent(randytrans);
//		e->AddComponent(randysprite);
//		e->AddComponent(randyshader);
//
//		entitymanager->AddEntity(e);
//
//		SpriteManager::InitSpriteGeometry();
//	}
//
//	void MainMenuScene::Render() const override
//	{
//		//sprite1->UseSprite();
//		//shader1->UseShader(mCamera, trans1->mTransform);
//		//SpriteManager::DrawSpriteGeometry();
//
//		//sprite2->UseSprite();
//		//shader2->UseShader(mCamera, trans2->mTransform);
//		//SpriteManager::DrawSpriteGeometry();
//
//	}
//
//	void MainMenuScene::Update() override
//	{
//		mCamera.UpdateCamera();
//
//		sysman->ExecuteSystems(entitymanager->mEntities);
//	}
//
//	void MainMenuScene::Close() override
//	{
//		ResourceManager::DeleteResources();
//		SpriteManager::ClearSpriteGeometry();
//	}
//
//	void MainMenuScene::ProcessKeyboardInput(GLFWwindow* pWindow, int pKey, int pScancode, int pAction, int pMods) override
//	{
//		if (pKey == GLFW_KEY_G && pAction == GLFW_PRESS)
//		{
//			Scene* newScene = new GameplayScene();
//			SceneManager::ChangeScene(newScene);
//		}
//	
//		if (pKey == GLFW_KEY_D && (pAction == GLFW_REPEAT || pAction == GLFW_PRESS))
//		{
//			mCamera.MoveCamera(RIGHT, 1.0f);
//		}
//
//		if (pKey == GLFW_KEY_A && (pAction == GLFW_REPEAT || pAction == GLFW_PRESS))
//		{
//			mCamera.MoveCamera(LEFT, 1.0f);
//		}
//
//		if (pKey == GLFW_KEY_W && (pAction == GLFW_REPEAT || pAction == GLFW_PRESS))
//		{
//			mCamera.MoveCamera(UP, 1.0f);
//		}
//
//		if (pKey == GLFW_KEY_S && (pAction == GLFW_REPEAT || pAction == GLFW_PRESS))
//		{
//			mCamera.MoveCamera(DOWN, 1.0f);
//		}
//
//		if (pKey == GLFW_KEY_E && (pAction == GLFW_REPEAT || pAction == GLFW_PRESS))
//		{
//			mCamera.MoveCamera(ZOOM_IN, 0.1f);
//		}
//
//		if (pKey == GLFW_KEY_Q && (pAction == GLFW_REPEAT || pAction == GLFW_PRESS))
//		{
//			mCamera.MoveCamera(ZOOM_OUT, 0.1f);
//		}
//
//		if (pKey == GLFW_KEY_X && pAction == GLFW_PRESS)
//		{
//			mCamera.ResetZoom();
//		}
//	}
//
//	void MainMenuScene::ProcessMouseInput(GLFWwindow* pWindow, double pXPos, double pYPos) override
//	{
//
//	}
