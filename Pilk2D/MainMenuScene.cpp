#include "Scene.h"
#include "SceneManager.h"

#include <glad.h>
#include <glfw3.h>
#include "ResourceManager.h"

#include "glm.hpp"
#include "gtc/matrix_transform.hpp"
#include "gtc/type_ptr.hpp"
#include "SpriteManager.h"

class MainMenuScene : public Scene
{
public:

	// TEMP VARS ----------------------------------

	unsigned int shaderProgID = 0;
	unsigned int texID = 0;
	unsigned int VAO = 0;
	int indexSize = 0;

	// Proj
	float aspect = (float)SceneManager::Width / SceneManager::Height;
	glm::mat4 proj = glm::ortho(-aspect, aspect, -1.0f, 1.0f, 10.0f, -10.0f);

	// Model
	glm::mat4 identity = glm::mat4(1.0f);
	glm::vec3 pos = glm::vec3(0.1f, 0.1f, 0.9f);
	glm::mat4 trans = glm::translate(identity, pos);

	// View
	glm::vec3 camPos = glm::vec3 (0.0f, 0.0f, -1.0f);
	glm::mat4 view = glm::lookAt(camPos, camPos + glm::vec3(0, 0, 1.0f), glm::vec3(0, 1, 0));

	// Colour
	float colour[4] = { 1.0f, 0.5f, 0.2f, 0.0f };
	
	// TEMP VARS ----------------------------------


	explicit MainMenuScene() : Scene()
	{ 
		SceneManager::WindowName = "Main Menu!";
	}

	~MainMenuScene() override
	{
		this->Close();
	}

	void Load() override
	{
		SpriteManager::InitSpriteGeometry();

		if (!ResourceManager::CreateShaderProgram(&shaderProgID, "resources/shaders/VertexShader.vert", "resources/shaders/FragmentShader.frag")) return;

		texID = ResourceManager::LoadTexture("resources/textures/grass.png");
	}

	void Render() const override
	{
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, texID);

		glUseProgram(shaderProgID);

		// Modify shader uniforms

		glUniform1i(glGetUniformLocation(shaderProgID, "uDiffuse"), 0);
		glUniformMatrix4fv(glGetUniformLocation(shaderProgID, "uModel"), 1, GL_FALSE, &(trans)[0][0]);
		glUniformMatrix4fv(glGetUniformLocation(shaderProgID, "uProjection"), 1, GL_FALSE, &(proj)[0][0]);
		glUniformMatrix4fv(glGetUniformLocation(shaderProgID, "uView"), 1, GL_FALSE, &(view)[0][0]);
		glUniform4f(glGetUniformLocation(shaderProgID, "uColour"), colour[0], colour[1], colour[2], colour[3]);
		glUniform1f(glGetUniformLocation(shaderProgID, "uTime"), glfwGetTime());

		SpriteManager::DrawSpriteGeometry();
	}

	void Update() override
	{
		view = glm::lookAt(camPos, camPos + glm::vec3(0, 0, 1.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	}

	void Close() override
	{
		ResourceManager::DeleteResources();
	}

	void ProcessKeyboardInput(GLFWwindow* pWindow, int pKey, int pScancode, int pAction, int pMods) override
	{
		if (pKey == GLFW_KEY_Q && pAction == GLFW_PRESS)
			SceneManager::ChangeScene(Gameplay);

		// FIX THIS, MOVEMENT BACKWARDS??
		if (pKey == GLFW_KEY_D && pAction == GLFW_REPEAT)
		{
			camPos.x += 1.0f * SceneManager::DeltaTime;
		}
	}

	void ProcessMouseInput(GLFWwindow* pWindow, double pXPos, double pYPos) override
	{

	}

private:
};