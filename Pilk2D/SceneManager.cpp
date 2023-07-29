#include "SceneManager.h"

#include <iostream>
#include <glad.h>
#include <glfw3.h>

#include "Scene.h"
#include "MainMenuScene.cpp"
#include "GameplayScene.cpp"
#include "ResourceManager.h"
#include "SpriteManager.h"

void SceneManager::Initialise(const int pWidth, const int pHeight, Scene* pStartScene)
{
    Width = pWidth;
    Height = pHeight;

    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // Create the window
    GLFWwindow* window = glfwCreateWindow(Width, Height, WindowName.c_str(), NULL, NULL);
    mWindow = window;

    if (mWindow == nullptr)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return;
    }
    // Set the window as the main context of the current thread
    glfwMakeContextCurrent(mWindow);

    // Initialize GLAD as it manages opengl function pointers
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return;
    }

    // Set viewport dimensions
    glViewport(0, 0, Width, Height);

    // Callbacks
    glfwSetFramebufferSizeCallback(mWindow, FrameBufferSizeCallback);
    glfwSetKeyCallback(mWindow, KeyboardKeyCallback);
    glfwSetCursorPosCallback(mWindow, CursorPositionCallback);

    // Init initial main menu scene
    ChangeScene(pStartScene);
}

void SceneManager::Run()
{
    if (mCurrentScene == nullptr)
    {
        std::cout << "Current scene is NULL" << std::endl;
        return;
    }

    float lastTime = static_cast<float>(glfwGetTime());

    while (!glfwWindowShouldClose(mWindow))
    {
        // Delta Time
        float now = static_cast<float>(glfwGetTime());
        DeltaTime = now - lastTime;
        lastTime = now;

        // Enable Depth Test
        glEnable(GL_DEPTH_TEST);

        // Clear colour
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        glClear(GL_DEPTH_BUFFER_BIT);

        mCurrentScene->Update();

        mCurrentScene->Render();

        glfwSwapBuffers(mWindow);
        glfwPollEvents();
    }

    ResourceManager::DeleteResources();
    SpriteManager::ClearSpriteGeometry();

    delete mCurrentScene;
    mCurrentScene = nullptr;
}

void SceneManager::ChangeScene(Scene* pNewScene)
{
    // Close current scene
    if (mCurrentScene != NULL)
    {
        CloseCurrentScene();
        delete mCurrentScene;
        mCurrentScene = nullptr;
    }

    mCurrentScene = pNewScene;

    // Load new scene
    LoadCurrentScene();

    glfwSetWindowTitle(mWindow, WindowName.c_str());
}

void SceneManager::RenderCurrentScene()
{
    mCurrentScene->Render();
}

void SceneManager::UpdateCurrentScene()
{
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
    mCurrentScene->ProcessMouseInput(pWindow, pXPos, pYPos);
}

void SceneManager::KeyboardKeyCallback(GLFWwindow* pWindow, int pKey, int pScancode, int pAction, int pMods)
{
	if (pKey == GLFW_KEY_ESCAPE && pAction == GLFW_PRESS)
		glfwSetWindowShouldClose(pWindow, true);

    mCurrentScene->ProcessKeyboardInput(pWindow, pKey, pScancode, pAction, pMods);
}

void SceneManager::FrameBufferSizeCallback(GLFWwindow* pWindow, int pWidth, int pHeight)
{
    Width = pWidth;
    Height = pHeight;
	glViewport(0, 0, pWidth, pHeight);
}
