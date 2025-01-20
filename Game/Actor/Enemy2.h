#pragma once

#include "Actor/DrawableActor.h"

class GameLevel;
class Enemy2 : public DrawableActor
{
	enum class Direction
	{
		None = -1,
		Left,
		Right
	};

	RTTI_DECLARATIONS(Enemy2, DrawableActor)

public:
	Enemy2(const char* image, int inputPositionY, GameLevel* level);

	virtual void Update(float deltaTime) override;

	virtual void SetPosition(const Vector2& newPosition) override;

	float speed = 1.0f;
	float factor = 0.0f;

	//void Move();

	//void SetGravity();

private:
	Direction direction = Direction::None;
	float xPosition = 0.0f;
	float yPosition = 0.0f;

	GameLevel* refLevel = nullptr;
};