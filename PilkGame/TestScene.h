#pragma once

#include <Scene.h>

class TestScene : public Scene
{

public:
	TestScene();
	~TestScene();

	virtual void Close() override;

	/// <summary>
	/// Render logic
	/// </summary>
	virtual void Render() const override;

	/// <summary>
	/// Update logic
	/// </summary>
	virtual void Update() override;

	/// <summary>
	/// Load logic
	/// </summary>
	virtual void Load() override;

	/// <summary>
	/// GUI Logic
	/// </summary>
	virtual void RenderGUI() override;

	/// <summary>
	/// Keyboard Input Processing
	/// </summary>
	virtual void ProcessKeyboardInput(GLFWwindow* pWindow, int pKey, int pScancode, int pAction, int pMods) override;

	/// <summary>
	/// Mouse Input Processing
	/// </summary>
	virtual void ProcessMouseInput(GLFWwindow* pWindow, double pXPos, double pYPos) override;

	bool operator==(const TestScene& other) const = default;
};