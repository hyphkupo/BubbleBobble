#pragma once

#include "Level/Level.h"
#include "Actor/DrawableActor.h"

class Wall;
class Ground;
class GameLevel : public Level
{
	// RTTI 적용.
	RTTI_DECLARATIONS(GameLevel, Level)

public:
	GameLevel();
	~GameLevel();

	virtual void Update(float deltaTime) override;

	bool IsOnGround = false;
	bool IsOnWall = true;
	bool IsInAir = false;

private:

private:
	// 벽/땅 액터 배열.
	List<DrawableActor*> map;

};