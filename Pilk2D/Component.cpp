#include "Component.h"
#include "glm.hpp"
#include "gtc/matrix_transform.hpp"
#include "gtc/type_ptr.hpp"
#include <string>
#include "ResourceManager.h"

#pragma region Component

Component::~Component() {}

#pragma endregion


#pragma region ComponentTransform

ComponentTransform::ComponentTransform(glm::vec2 pTranslation, float pAngle, glm::vec2 pScale, int pLayer) {

	mTranslation = pTranslation;
	mAngle = pAngle;
	mScale = pScale;
	mLayer = pLayer;
	mTransform = glm::mat4(1.0f);

	UpdateTransform();
}

ComponentTransform::~ComponentTransform() {}

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

#pragma region ComponentSprite

ComponentSprite::ComponentSprite(const std::string& pFilename) 
{
	mTextureBuffer =  ResourceManager::LoadTexture(pFilename);
}

ComponentSprite::~ComponentSprite()
{

}

unsigned int ComponentSprite::GetTextureBuffer()
{
	return mTextureBuffer;
}

#pragma endregion
