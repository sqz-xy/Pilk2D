#include "Scene.h"
#include "SceneManager.h"

class MainMenuScene : public Scene
{
public:
	explicit MainMenuScene() : Scene()
	{ 
		SceneManager::WindowName = "Main Menu!";
	}

	~MainMenuScene() override
	{
		this->Close();
	}

	void Load() override
	{

	}

	void Render() const override
	{

	}

	void Update() override
	{

	}

	void ProcessKeyboardInput(GLFWwindow* pWindow, int pKey, int pScancode, int pAction, int pMods) override
	{

	}

	void ProcessMouseInput(GLFWwindow* pWindow, double pXPos, double pYPos) override
	{

	}

private:
};