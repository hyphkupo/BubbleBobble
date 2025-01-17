#pragma once

#include "Level/Level.h"
#include "Actor/DrawableActor.h"

class Wall;
class Ground;
class GameLevel : public Level
{
	// RTTI ����.
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
	// ��/�� ���� �迭.
	List<DrawableActor*> map;

};