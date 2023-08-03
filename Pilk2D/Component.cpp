#include "Component.h"
#include "glm.hpp"
#include "gtc/matrix_transform.hpp"
#include "gtc/type_ptr.hpp"
#include <string>
#include "ResourceManager.h"
#include <glfw3.h>
#include "Camera.h"

#pragma region Component

Component::~Component() {}

#pragma endregion

#pragma region ComponentTransform

ComponentTransform::ComponentTransform(glm::vec2 pTranslation, float pAngle, glm::vec2 pScale, float pLayer) {

	mTranslation = pTranslation;
	mAngle = pAngle;
	mScale = pScale;
	mLayer = pLayer;
	mTransform = glm::mat4(1.0f);

	UpdateTransform();
}

ComponentTransform::~ComponentTransform() 
{
}

void ComponentTransform::UpdateTranslation(glm::vec2 pTranslation) {
	mTranslation = pTranslation;

	UpdateTransform();
}

void ComponentTransform::UpdateScale(glm::vec2 pScale) {
	mScale = pScale;

	UpdateTransform();
}


void ComponentTransform::UpdateRotation(float pAngle) {
	mAngle = pAngle;

	UpdateTransform();
}

void ComponentTransform::UpdateTransform() {

	glm::mat4 identity(1.0f);

	glm::vec3 tempTranslation = glm::vec3(mTranslation.x, mTranslation.y, mLayer);
	glm::mat4 translationMat = glm::translate(identity, tempTranslation);

	glm::vec3 tempScale = glm::vec3(mScale.x, mScale.y, 0);
	glm::mat4 scaleMat = glm::scale(translationMat, tempScale);

	glm::mat4 rotationMat = glm::rotate(scaleMat, mAngle, glm::vec3(1, 0, 0));

	mTransform = rotationMat;
}


#pragma endregion

#pragma region Component Physics

ComponentPhysics::ComponentPhysics()
{
	mVelocity = glm::vec2(0, 0);
}

ComponentPhysics::~ComponentPhysics() 
{

}

#pragma endregion

#pragma region ComponentSprite

ComponentSprite::ComponentSprite(const std::string& pFilename) 
{
	mTextureBuffer =  ResourceManager::LoadTexture(pFilename);
}

ComponentSprite::~ComponentSprite()
{

}

void ComponentSprite::UseSprite()
{
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, mTextureBuffer);
}

unsigned int ComponentSprite::GetTextureBuffer()
{
	return mTextureBuffer;
}

#pragma endregion

#pragma region ComponentShader

ComponentShader::ComponentShader(const std::string& pVertexFileName, const std::string& pFragmentFileName)
{
	if (!ResourceManager::CreateShaderProgram(&mShaderHandle, pVertexFileName, pFragmentFileName)) return;
}

ComponentShader::~ComponentShader()
{
	// Clear shader buffer
}

void ComponentShader::UseShader(const Camera& pCamera, glm::mat4 pTransform)
{
	glUseProgram(mShaderHandle);
	glUniformMatrix4fv(glGetUniformLocation(mShaderHandle, "uModel"), 1, GL_FALSE, &(pTransform)[0][0]);
	glUniformMatrix4fv(glGetUniformLocation(mShaderHandle, "uView"), 1, GL_FALSE, &(pCamera.mView)[0][0]);
	glUniformMatrix4fv(glGetUniformLocation(mShaderHandle, "uProjection"), 1, GL_FALSE, &(pCamera.mProjection)[0][0]);

	// TEMP SOLUTION FOR PROOF OF CONCEPT
	glUniform1i(glGetUniformLocation(mShaderHandle, "uPanelIndex"), static_cast<GLfloat>(index++));

	if (index == 6)
		index = 0;

	glUniform1f(glGetUniformLocation(mShaderHandle, "uTime"), static_cast<GLfloat>(glfwGetTime()));
}

inline unsigned int ComponentShader::GetHandle()
{
	return mShaderHandle;
}

#pragma endregion

#pragma region ComponentCollisionAABB

ComponentCollisionAABB::ComponentCollisionAABB(float pWidth, float pHeight)
{
	mWidth = pWidth;
	mHeight = pHeight;
}

ComponentCollisionAABB::~ComponentCollisionAABB()
{

}

#pragma endregion

