#pragma once

#include <string>

struct ImGuiIO;

class ImGUIManager final
{
public:
	ImGUIManager(ImGUIManager& pOther) = delete;
	void operator=(const ImGUIManager& pRhs) = delete;

	static ImGUIManager* GetInstance();
	static void KillInstance();
	static void StartFrame();
	static void EndFrame();

	ImGuiIO* mIO = nullptr;

protected:
	ImGUIManager();
	~ImGUIManager();

	static ImGUIManager* mInstance;
};


