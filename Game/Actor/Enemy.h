#pragma once

#include "Actor/DrawableActor.h"

class GameLevel;
class Enemy : public DrawableActor
{
	// �� ĳ���Ͱ� �̵��� ����.
	enum class Direction
	{
		None = -1,
		Left,
		Right
	};

	RTTI_DECLARATIONS(Enemy, DrawableActor)

public:
	Enemy(const char* image, int inputPositionY, GameLevel* level);

	virtual void Update(float deltaTime) override;

	virtual void SetPosition(const Vector2& newPosition) override;

	bool inBubble = false;

private:
	Direction direction = Direction::None;
	float xPosition = 0.0f;
	float yPosition = 0.0f;

	float speed = 3.0f;
	float factor = 0.0f;
	
	GameLevel* refLevel = nullptr;
};