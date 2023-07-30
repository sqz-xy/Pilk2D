#pragma once

#include "Scene.h"
#include "SceneManager.h"

//TODO: Implement gang of three
Scene::Scene()
{
	mSceneManagerInstance = SceneManager::GetInstance();
}

Scene::~Scene() = default;