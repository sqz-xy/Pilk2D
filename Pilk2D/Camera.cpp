#pragma once


#include "Camera.h"
#include <iostream>
#include "SceneManager.h"


/// Original Author: Thomas Beet
/// <summary>
/// Camera values intialisation
/// </summary>
Camera::Camera(const glm::vec3 pPos, const glm::vec3 pTarget)
{
	mSceneManagerInstance = SceneManager::GetInstance();

	// Vecs
	mCameraPos = pPos;
	mCameraTarget = pTarget;
	mCameraDirection = glm::vec3(glm::normalize(pTarget - pPos));
	mCameraRight = glm::normalize(glm::cross(mCameraUp, mCameraDirection));

	// Mats
	float aspect = (float)mSceneManagerInstance->Width / mSceneManagerInstance->Width;
	mProjection = glm::ortho(-aspect, aspect, -1.0f, 1.0f, 10.0f, -10.0f);
	mView = glm::inverse(mProjection);
	//mView = glm::lookAt(mCameraPos, mCameraPos + mCameraDirection, mCameraUp);

}

Camera::~Camera()
{

}

/// Original Author: Thomas Beet
/// <summary>
/// Movesd the camera in a given direction a given distance
/// </summary>
void Camera::MoveCamera(const CameraActions pAction, const float pDistance)
{
	const float camSpeed = pDistance * mSceneManagerInstance->DeltaTime;

	switch (pAction)
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
	case ZOOM_IN:
		if (mZoom - pDistance <= 0)
			break;
		mZoom -= pDistance;
		break;
	case ZOOM_OUT:
		mZoom += pDistance;
		break;
	default:
		break;
	}

	std::cout << "CamPos: X:" << mCameraPos.x << " Y: " << mCameraPos.y << " Z: " << mCameraPos.z << "\n" << "CamZoom: " << mZoom << '\n';
}

void Camera::ResetZoom()
{
	mZoom = 1.0f;
}

/// Original Author: Thomas Beet
/// <summary>
/// Updates the view matrix
/// </summary>
void Camera::UpdateCamera()
{
	float aspect = (static_cast<float>(mSceneManagerInstance->Width)) / (mSceneManagerInstance->Height);
	mView = glm::lookAt(mCameraPos, mCameraPos + mCameraDirection, mCameraUp);
	mProjection = glm::ortho(-aspect * mZoom, aspect * mZoom, -1.0f * mZoom, 1.0f * mZoom, 10.0f, -10.0f);
}
	
