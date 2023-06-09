#pragma once

#include <string>

struct GLFWwindow;
class Scene;
enum SceneType;

class SceneManager final
{
public:
	static void Initialise(const int pWidth, const int pHeight, std::string& pWindowName);
	static void Run();
	static void ChangeScene(SceneType pSceneType);

	// Static game variables, across the program
	inline static int Width;
	inline static int Height;
	inline static std::string WindowName;
	inline static float DeltaTime;

private:
	SceneManager() = delete;
	~SceneManager() = delete;

	static void RenderCurrentScene();
	static void UpdateCurrentScene();
	static void LoadCurrentScene();
	static void CloseCurrentScene();

	static void CursorPositionCallback(GLFWwindow* pWindow, double pXPos, double pYPos);
	static void KeyboardKeyCallback(GLFWwindow* pWindow, int pKey, int pScancode, int pAction, int pMods);
	static void FrameBufferSizeCallback(GLFWwindow* pWindow, int pWidth, int pHeight);

	inline static Scene* mCurrentScene;

	inline static GLFWwindow* mWindow;
};