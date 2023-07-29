//#include "Scene.h"
//#include "SceneManager.h"
//#include "ResourceManager.h"
//#include "MainMenuScene.h"
//#include <glfw3.h>
//
//class GameplayScene : public Scene
//{
//public:
//	explicit GameplayScene() : Scene()
//	{
//		SceneManager::WindowName = "Gameplay!";
//	}
//
//	~GameplayScene() override
//	{
//		this->Close();
//	}
//
//	void Load() override
//	{
//
//	}
//
//	void Render() const override
//	{
//
//	}
//
//	void Update() override
//	{
//
//	}
//
//	void Close() override
//	{
//		ResourceManager::DeleteResources();
//	}
//
//	void ProcessKeyboardInput(GLFWwindow* pWindow, int pKey, int pScancode, int pAction, int pMods) override
//	{
//		if (pKey == GLFW_KEY_E && pAction == GLFW_PRESS)
//		{
//			Scene* newScene = new MainMenuScene();
//			SceneManager::ChangeScene(newScene);
//		}
//
//	}
//
//	void ProcessMouseInput(GLFWwindow* pWindow, double pXPos, double pYPos) override
//	{
//
//	}
//
//private:
//};