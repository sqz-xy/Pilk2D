#pragma once

class SpriteManager final
{
protected:
	SpriteManager();
	~SpriteManager();

	static SpriteManager* mInstance;

public:
	SpriteManager(SpriteManager& pOther) = delete;
	void operator=(const SpriteManager& pRhs) = delete;

	static SpriteManager* GetInstance();
	static void KillInstance();
	static bool InitSpriteGeometry();
	static bool DrawSpriteGeometry();
	static bool ClearSpriteGeometry();

private:
	unsigned int mSpriteVAO = -1;
	unsigned int mSpriteVBO = -1;
	unsigned int mSpriteEBO = -1;
	unsigned int mIndexSize = -1;
};

