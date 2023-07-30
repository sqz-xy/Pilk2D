#include <SceneManager.h>
#include "TestScene.h"

/**
 * \brief The main program
 * \return exit code
 */
int main()
{
    Scene* mainMenu = new TestScene();
    SceneManager::Initialise(800, 600, mainMenu);
    SceneManager::Run();

    SceneManager::KillInstance();
    return 0;
}