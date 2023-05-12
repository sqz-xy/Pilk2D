#pragma once

class SpriteManager final
{
public:

	static bool InitSpriteGeometry();
	static bool DrawSpriteGeometry();
	static bool ClearSpriteGeometry();

private:
	SpriteManager() = delete;
	~SpriteManager() = delete;

	inline static unsigned int mSpriteVAO = -1;
	inline static unsigned int mSpriteVBO = -1;
	inline static unsigned int mSpriteEBO = -1;
	inline static unsigned int mIndexSize = -1;
};

