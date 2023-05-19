#pragma once

#include "glm.hpp"
#include "gtc/matrix_transform.hpp"
#include "gtc/type_ptr.hpp"

class Component
{
public:
	virtual ~Component() = 0;
};

class ComponentTransform : public Component {

public:
	explicit ComponentTransform(glm::vec2 pTranslation, float pAngle, glm::vec2 pScale, int pLayer);

	glm::vec3 mTranslation;
	float mAngle;
	glm::vec2 mScale;
	int mLayer;
	glm::mat4 mTranslate;

	void UpdateTranslation(glm::vec3 pTranslation);
	void UpdateScale(glm::vec2 pScale);
	void UpdateRotation(float pAngle);

private:

	void UpdateTransform();

};