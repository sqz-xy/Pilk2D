#include "SpriteManager.h"

#include <glad.h>
#include <iostream>

bool SpriteManager::InitSpriteGeometry()
{
	if (mSpriteVAO != -1)
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

	mIndexSize = sizeof(indices);

	glGenVertexArrays(1, &mSpriteVAO);
	glGenBuffers(1, &mSpriteVBO);
	glGenBuffers(1, &mSpriteEBO);

	glBindVertexArray(mSpriteVAO);

	glBindBuffer(GL_ARRAY_BUFFER, mSpriteVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mSpriteEBO);
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

	glBindVertexArray(mSpriteVAO);
	glDrawElements(GL_TRIANGLES, mIndexSize / sizeof(unsigned int), GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);

	return true;
}

bool SpriteManager::ClearSpriteGeometry()
{
	if (mSpriteVAO == -1)
	{
		std::cout << "Data not bound" << std::endl;
		return false;
	}

	glDeleteBuffers(1, &mSpriteVBO);
	glDeleteVertexArrays(1, &mSpriteVAO);
	glDeleteBuffers(1, &mSpriteEBO);

	mSpriteVBO = -1;
	mSpriteVAO = -1;
	mSpriteEBO = -1;

	return true;
}
