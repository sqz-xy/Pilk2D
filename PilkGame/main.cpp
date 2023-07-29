#include <SceneManager.h>

/**
 * \brief The main program
 * \return exit code
 */
int main()
{
    std::string windowName = "Balls";
    SceneManager::Initialise(800, 600, windowName);
    SceneManager::Run();

    return 0;
}