#pragma once

#include <string>
#include "glm.hpp"
#include "gtc/matrix_transform.hpp"
#include "gtc/type_ptr.hpp"

class Component
{
public:
	virtual ~Component();
};

class ComponentTransform : public Component {

public:
	ComponentTransform(glm::vec2 pTranslation, float pAngle, glm::vec2 pScale, int pLayer);
	~ComponentTransform();

	glm::vec2 mTranslation;
	float mAngle;
	glm::vec2 mScale;
	int mLayer;
	glm::mat4 mTransform;

	void UpdateTranslation(glm::vec2 pTranslation);
	void UpdateScale(glm::vec2 pScale);
	void UpdateRotation(float pAngle);

private:

	void UpdateTransform();

};

class ComponentSprite : public Component {

public:

	ComponentSprite(const std::string& pFilename);
	~ComponentSprite();

	unsigned int GetTextureBuffer();

private:

	unsigned int mTextureBuffer;

};