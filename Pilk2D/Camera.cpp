#pragma once


#include "Camera.h"
#include <iostream>
#include "SceneManager.h"


/// Original Author: Thomas Beet
/// <summary>
/// Camera values intialisation
/// </summary>
Camera::Camera(const glm::vec3 p_pos, const glm::vec3 p_target)
{
	// Vecs
	mCameraPos = p_pos;
	mCameraTarget = p_target;
	mCameraDirection = glm::vec3(glm::normalize(p_target - p_pos));
	mCameraRight = glm::normalize(glm::cross(mCameraUp, mCameraDirection));

	// Mats
	float aspect = (float)SceneManager::Width / SceneManager::Height;
	mProjection = glm::ortho(-aspect, aspect, -1.0f, 1.0f, 10.0f, -10.0f);
	mView = glm::lookAt(mCameraPos, mCameraPos + mCameraDirection, mCameraUp);

}

Camera::~Camera()
{

}


/// Original Author: Thomas Beet
/// <summary>
/// Movesd the camera in a given direction a given distance
/// </summary>
void Camera::MoveCamera(const Direction p_direction, const float p_distance)
{
	const float camSpeed = p_distance * SceneManager::DeltaTime;

	switch (p_direction)
	{
	case LEFT:
		mCameraPos += mCameraRight * camSpeed;
		break;
	case RIGHT:
		mCameraPos -= mCameraRight * camSpeed;
		break;
	case UP:
		mCameraPos += mCameraUp * camSpeed;
		break;
	case DOWN:
		mCameraPos -= mCameraUp * camSpeed;
		break;
	default:
		break;
	}

	std::cout << "CamPos: X:" << mCameraPos.x << " Y: " << mCameraPos.y << " Z: " << mCameraPos.z << '\n';
}

/// Original Author: Thomas Beet
/// <summary>
/// Updates the view matrix
/// </summary>
void Camera::UpdateCamera()
{
	float aspect = (float)SceneManager::Width / SceneManager::Height;
	mView = glm::lookAt(mCameraPos, mCameraPos + mCameraDirection, mCameraUp);
	mProjection = glm::ortho(-aspect, aspect, -1.0f, 1.0f, 10.0f, -10.0f);
}
	
