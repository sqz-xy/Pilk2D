#include "SceneManager.h"

#include <iostream>
#include <glad.h>
#include <glfw3.h>

#include "Scene.h"
#include "MainMenuScene.cpp"
#include "GameplayScene.cpp"
#include "ResourceManager.h"
#include "SpriteManager.h"

SceneManager* SceneManager::mInstance = nullptr;

void SceneManager::Initialise(const int pWidth, const int pHeight, Scene* pStartScene)
{
    SceneManager* SceneManager = GetInstance();

    SceneManager->Width = pWidth;
    SceneManager->Height = pHeight;

    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // Create the window
    GLFWwindow* window = glfwCreateWindow(SceneManager->Width, SceneManager->Height, SceneManager->WindowName.c_str(), NULL, NULL);
    SceneManager->mWindow = window;

    if (SceneManager->mWindow == nullptr)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return;
    }
    // Set the window as the main context of the current thread
    glfwMakeContextCurrent(SceneManager->mWindow);

    // Initialize GLAD as it manages opengl function pointers
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return;
    }

    // Set viewport dimensions
    glViewport(0, 0, SceneManager->Width, SceneManager->Height);

    // Callbacks
    glfwSetFramebufferSizeCallback(SceneManager->mWindow, FrameBufferSizeCallback);
    glfwSetKeyCallback(SceneManager->mWindow, KeyboardKeyCallback);
    glfwSetCursorPosCallback( SceneManager->mWindow, CursorPositionCallback);

    // Init initial main menu scene
    ChangeScene(pStartScene);
}

void SceneManager::Run()
{
    SceneManager* SceneManager = GetInstance();

    if (SceneManager->mCurrentScene == nullptr)
    {
        std::cout << "Current scene is NULL" << std::endl;
        return;
    }

    float lastTime = static_cast<float>(glfwGetTime());

    while (!glfwWindowShouldClose(SceneManager->mWindow))
    {
        // Delta Time
        float now = static_cast<float>(glfwGetTime());
        SceneManager->DeltaTime = now - lastTime;
        lastTime = now;

        // Enable Depth Test
        glEnable(GL_DEPTH_TEST);

        // Clear colour
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        glClear(GL_DEPTH_BUFFER_BIT);

        SceneManager->mCurrentScene->Update();

        SceneManager->mCurrentScene->Render();

        glfwSwapBuffers(SceneManager->mWindow);
        glfwPollEvents();
    }

    ResourceManager::DeleteResources();
    SpriteManager::ClearSpriteGeometry();

    delete SceneManager->mCurrentScene;
    SceneManager->mCurrentScene = nullptr;

    ResourceManager::KillInstance();
    SpriteManager::KillInstance();

    glfwTerminate();
}

void SceneManager::ChangeScene(Scene* pNewScene)
{
    SceneManager* SceneManager = GetInstance();

    // Close current scene
    if (SceneManager->mCurrentScene != NULL)
    {
        SceneManager->CloseCurrentScene();
        delete SceneManager->mCurrentScene;
        SceneManager->mCurrentScene = nullptr;
    }

    SceneManager->mCurrentScene = pNewScene;

    // Load new scene
    SceneManager->LoadCurrentScene();

    glfwSetWindowTitle(SceneManager->mWindow, SceneManager->WindowName.c_str());
}

SceneManager::SceneManager()
{
}

SceneManager::~SceneManager()
{
}

SceneManager* SceneManager::GetInstance()
{
    if (mInstance == nullptr)
    {
        mInstance = new SceneManager();
    }

    return mInstance;
}

void SceneManager::KillInstance()
{
    if (mInstance != nullptr)
    {
        delete mInstance;
    }
}

void SceneManager::RenderCurrentScene()
{
    mCurrentScene->Render();
}

void SceneManager::UpdateCurrentScene()
{
    SceneManager* SceneManager = GetInstance();
    // Temp
    SceneManager->mCurrentScene->ProcessKeyboardInput(SceneManager->mWindow, -1, -1, -1, -1);
    mCurrentScene->Update();
}

void SceneManager::LoadCurrentScene()
{
    mCurrentScene->Load();
    glfwSetWindowTitle(mWindow, WindowName.c_str());
}

void SceneManager::CloseCurrentScene()
{
    mCurrentScene->Close();
}

void SceneManager::CursorPositionCallback(GLFWwindow* pWindow, double pXPos, double pYPos)
{
    SceneManager* SceneManager = GetInstance();
    SceneManager->mCurrentScene->ProcessMouseInput(pWindow, pXPos, pYPos);
}

void SceneManager::KeyboardKeyCallback(GLFWwindow* pWindow, int pKey, int pScancode, int pAction, int pMods)
{
    SceneManager* SceneManager = GetInstance();

	if (pKey == GLFW_KEY_ESCAPE && pAction == GLFW_PRESS)
		glfwSetWindowShouldClose(pWindow, true);

    SceneManager->mCurrentScene->ProcessKeyboardInput(pWindow, pKey, pScancode, pAction, pMods);
}

void SceneManager::FrameBufferSizeCallback(GLFWwindow* pWindow, int pWidth, int pHeight)
{
    SceneManager* SceneManager = GetInstance();

    SceneManager->Width = pWidth;
    SceneManager->Height = pHeight;
	glViewport(0, 0, pWidth, pHeight);
}
