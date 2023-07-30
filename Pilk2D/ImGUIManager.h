#pragma once
class ImGUIManager final
{
public:
	ImGUIManager(ImGUIManager& pOther) = delete;
	void operator=(const ImGUIManager& pRhs) = delete;

	static ImGUIManager* GetInstance();
	static void KillInstance();

protected:
	ImGUIManager();
	~ImGUIManager();

	static ImGUIManager* mInstance;
};


