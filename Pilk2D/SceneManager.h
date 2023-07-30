#pragma once

#include <string>

struct GLFWwindow;
class Scene;
enum SceneType;

class SceneManager final
{
public:
	static void Initialise(const int pWidth, const int pHeight, Scene* pStartScene);
	static void Run();
	static void ChangeScene(Scene* pNewScene);

	static SceneManager* GetInstance();
	static void KillInstance();

	// Static game variables, across the program
	int Width = 0;
	int Height = 0;
	std::string WindowName = "";
	float DeltaTime = 0.0f;
	GLFWwindow* Window = nullptr;

protected:
	SceneManager();
	~SceneManager();

	static SceneManager* mInstance;

	void RenderCurrentScene();
	void UpdateCurrentScene();
	void LoadCurrentScene();
	void CloseCurrentScene();
	void RenderSceneGUI();

	static void CursorPositionCallback(GLFWwindow* pWindow, double pXPos, double pYPos);
	static void KeyboardKeyCallback(GLFWwindow* pWindow, int pKey, int pScancode, int pAction, int pMods);
	static void FrameBufferSizeCallback(GLFWwindow* pWindow, int pWidth, int pHeight);

	Scene* mCurrentScene = nullptr;
};