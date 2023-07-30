#pragma once

#include "glm.hpp"
#include "gtc/matrix_transform.hpp"
#include "gtc/type_ptr.hpp"

class SceneManager;

enum CameraActions
{
	UP,
	DOWN,
	LEFT,
	RIGHT,
	ZOOM_IN,
	ZOOM_OUT
};

/// Original Author: Thomas Beet, edited by James and Piotr
/// <summary>
/// Camera declarations
/// </summary>
class Camera final
{
public:
	glm::vec3 mCameraPos;
	glm::vec3 mCameraTarget;
	glm::vec3 mCameraDirection;
	glm::vec3 mCameraRight;
	const glm::vec3 mCameraUp = glm::vec3(0.0f, 1.0f, 0.0f);

	glm::mat4 mView;
	glm::mat4 mProjection;

	float mZoom = 1.0f;

	explicit Camera(const glm::vec3 pPos, const glm::vec3 pTarget);
	~Camera();

	void MoveCamera(const CameraActions pAction, const float pDistance);
	void ResetZoom();
	void UpdateCamera();

private:
	SceneManager* mSceneManagerInstance;
};