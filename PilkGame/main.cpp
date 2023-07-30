#include <SceneManager.h>
#include "TestScene.h"

/**
 * \brief The main program
 * \return exit code
 */
int main()
{
    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

    Scene* mainMenu = new TestScene();
    SceneManager::Initialise(1280, 960, mainMenu);
    SceneManager::Run();

    SceneManager::KillInstance();
    return 0;
}