#include "Scene.h"
#include "SceneManager.h"

#include <glad.h>
#include <glfw3.h>
#include "ResourceManager.h"

#include "glm.hpp"
#include "gtc/matrix_transform.hpp"
#include "gtc/type_ptr.hpp"
#include "SpriteManager.h"
#include "Camera.h"

class MainMenuScene : public Scene
{
public:

	// TEMP VARS ----------------------------------

	unsigned int shaderProgID = 0;
	unsigned int texID = 0;
	unsigned int texID2 = 0;

	// Model
	glm::mat4 identity = glm::mat4(1.0f);
	glm::vec3 pos = glm::vec3(0.0f, 0.0f, 0.9f);  //RANDY
	glm::vec3 pos2 = glm::vec3(0.0f, 0.2f, 1.0f); //GRASS  // +Z = Closer to the camera

	glm::mat4 trans = glm::translate(identity, pos);
	glm::mat4 trans2 = glm::translate(identity, pos2);

	//						POS							  TARGET
	Camera mCamera = Camera(glm::vec3(0.0f, 0.0f, -1.0f), glm::vec3(0.0f, 0.0f, 1.0f));

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
		texID2 = ResourceManager::LoadTexture("resources/textures/capsule.jpg");
	}

	void Render() const override
	{
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, texID);

		glUseProgram(shaderProgID);

		// Modify shader uniforms
		glUniform1i(glGetUniformLocation(shaderProgID, "uDiffuse"), 0);
		glUniformMatrix4fv(glGetUniformLocation(shaderProgID, "uModel"), 1, GL_FALSE, &(trans)[0][0]);
		glUniformMatrix4fv(glGetUniformLocation(shaderProgID, "uProjection"), 1, GL_FALSE, &(mCamera.mProjection)[0][0]);
		glUniformMatrix4fv(glGetUniformLocation(shaderProgID, "uView"), 1, GL_FALSE, &(mCamera.mView)[0][0]);
		glUniform4f(glGetUniformLocation(shaderProgID, "uColour"), colour[0], colour[1], colour[2], colour[3]);
		glUniform1f(glGetUniformLocation(shaderProgID, "uTime"), glfwGetTime());

		SpriteManager::DrawSpriteGeometry();

		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, texID2);

		glUniform1i(glGetUniformLocation(shaderProgID, "uDiffuse"), 0);
		glUniformMatrix4fv(glGetUniformLocation(shaderProgID, "uModel"), 1, GL_FALSE, &(trans2)[0][0]);

		SpriteManager::DrawSpriteGeometry();

	}

	void Update() override
	{
		mCamera.UpdateCamera();
	}

	void Close() override
	{
		ResourceManager::DeleteResources();
		SpriteManager::ClearSpriteGeometry();
	}

	void ProcessKeyboardInput(GLFWwindow* pWindow, int pKey, int pScancode, int pAction, int pMods) override
	{
		if (pKey == GLFW_KEY_Q && pAction == GLFW_PRESS)
			SceneManager::ChangeScene(Gameplay);

		if (pKey == GLFW_KEY_D && pAction == GLFW_REPEAT)
		{
			mCamera.MoveCamera(RIGHT, 1.0f);
		}

		if (pKey == GLFW_KEY_A && pAction == GLFW_REPEAT)
		{
			mCamera.MoveCamera(LEFT, 1.0f);
		}

		if (pKey == GLFW_KEY_W && pAction == GLFW_REPEAT)
		{
			mCamera.MoveCamera(UP, 1.0f);
		}

		if (pKey == GLFW_KEY_S && pAction == GLFW_REPEAT)
		{
			mCamera.MoveCamera(DOWN, 1.0f);
		}
	}

	void ProcessMouseInput(GLFWwindow* pWindow, double pXPos, double pYPos) override
	{

	}

private:
};