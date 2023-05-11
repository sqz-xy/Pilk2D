#include "SceneManager.h"

/**
 * \brief The main program
 * \return exit code
 */
int main()
{
    std::string windowName = "Balls";
    SceneManager::Initialise(600, 600, windowName);
    SceneManager::Run();
    
    return 0;
}