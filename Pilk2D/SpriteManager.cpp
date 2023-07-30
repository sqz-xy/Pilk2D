#include "SpriteManager.h"

#include <glad.h>
#include <iostream>

SpriteManager* SpriteManager::mInstance = nullptr;

SpriteManager::SpriteManager()
{
}

SpriteManager::~SpriteManager()
{
}

SpriteManager* SpriteManager::GetInstance()
{
	if (mInstance == nullptr)
	{
		mInstance = new SpriteManager();
	}

	return mInstance;
}

void SpriteManager::KillInstance()
{
	if (mInstance != nullptr)
	{
		delete mInstance;
	}
}

bool SpriteManager::InitSpriteGeometry()
{
	SpriteManager* SpriteManager = GetInstance();

	if (SpriteManager->mSpriteVAO != -1)
	{
		std::cout << "Data already bound" << std::endl;
		return false;
	}

	// GEOMETRY
	float vertices[] = {
		// positions          // normals          // texture coords
		 0.5f,  0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   1.0f, 1.0f, // top right
		 0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   1.0f, 0.0f, // bottom right
		-0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f, // bottom left
		-0.5f,  0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 1.0f  // top left 
	};

	unsigned int indices[] = {
		0, 1, 3, // first triangle
		1, 2, 3  // second triangle
	};

	SpriteManager->mIndexSize = sizeof(indices);

	glGenVertexArrays(1, &SpriteManager->mSpriteVAO);
	glGenBuffers(1, &SpriteManager->mSpriteVBO);
	glGenBuffers(1, &SpriteManager->mSpriteEBO);

	glBindVertexArray(SpriteManager->mSpriteVAO);

	glBindBuffer(GL_ARRAY_BUFFER, SpriteManager->mSpriteVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, SpriteManager->mSpriteEBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	// position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	// normal attribute
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	// texture coord attribute
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	glEnableVertexAttribArray(2);

	glBindVertexArray(0);

	return true;
}

bool SpriteManager::DrawSpriteGeometry()
{
	//TODO: Add checks

	SpriteManager* SpriteManager = GetInstance();

	glBindVertexArray(SpriteManager->mSpriteVAO);
	glDrawElements(GL_TRIANGLES, SpriteManager->mIndexSize / sizeof(unsigned int), GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);

	return true;
}

bool SpriteManager::ClearSpriteGeometry()
{

	SpriteManager* SpriteManager = GetInstance();

	if (SpriteManager->mSpriteVAO == -1)
	{
		std::cout << "Data not bound" << std::endl;
		return false;
	}

	glDeleteBuffers(1, &SpriteManager->mSpriteVBO);
	glDeleteVertexArrays(1, &SpriteManager->mSpriteVAO);
	glDeleteBuffers(1, &SpriteManager->mSpriteEBO);

	SpriteManager->mSpriteVBO = -1;
	SpriteManager->mSpriteVAO = -1;
	SpriteManager->mSpriteEBO = -1;

	return true;
}
