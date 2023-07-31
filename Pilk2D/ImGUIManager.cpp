#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

#include "ImGUIManager.h"
#include "SceneManager.h"

ImGUIManager* ImGUIManager::mInstance = nullptr;

ImGUIManager::ImGUIManager()
{
}

ImGUIManager::~ImGUIManager()
{
}

ImGUIManager* ImGUIManager::GetInstance()
{
	if (mInstance == nullptr)
	{
		mInstance = new ImGUIManager();

		SceneManager* SceneManagerInstance = SceneManager::GetInstance();

		IMGUI_CHECKVERSION();
		ImGui::CreateContext();
		mInstance->mIO = &ImGui::GetIO();
		mInstance->mIO->ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
		mInstance->mIO->ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls

		ImGui_ImplGlfw_InitForOpenGL(SceneManagerInstance->Window, true);          // Second param install_callback=true will install GLFW callbacks and chain to existing ones.
		ImGui_ImplOpenGL3_Init();
	}
	return mInstance;
}

void ImGUIManager::KillInstance()
{
	if (mInstance != nullptr)
	{
		ImGui_ImplOpenGL3_Shutdown();
		ImGui_ImplGlfw_Shutdown();
		ImGui::DestroyContext();

		delete mInstance;
	}
}

void ImGUIManager::StartFrame()
{
	// Ensures initialisation has occured
	GetInstance();

	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();
}

void ImGUIManager::EndFrame()
{
	// Ensures initialisation has occured
	GetInstance();

	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}


