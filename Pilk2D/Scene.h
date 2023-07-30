#pragma once

struct GLFWwindow;
class SceneManager;

// By Thomas Beet
class Scene
{
public:
	explicit Scene();
	virtual ~Scene();

	virtual void Close() = 0;

	/// <summary>
	/// Render logic
	/// </summary>
	virtual void Render() const = 0;

	/// <summary>
	/// Update logic
	/// </summary>
	virtual void Update() = 0;

	/// <summary>
	/// Load logic
	/// </summary>
	virtual void Load() = 0;

	/// <summary>
	/// GUI Logic
	/// </summary>
	virtual void RenderGUI() = 0;

	/// <summary>
	/// Keyboard Input Processing
	/// </summary>
	virtual void ProcessKeyboardInput(GLFWwindow* pWindow, int pKey, int pScancode, int pAction, int pMods) = 0;

	/// <summary>
	/// Mouse Input Processing
	/// </summary>
	virtual void ProcessMouseInput(GLFWwindow* pWindow, double pXPos, double pYPos) = 0;

protected:
	SceneManager* mSceneManagerInstance;
};


