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
	Enemy(const char* image);

	virtual void Update(float deltaTime) override;

	//void Move();

	void SetGravity();

private:
	Direction direction = Direction::None;
	float xPosition = 0.0f;
	float speed = 1.0f;

	GameLevel* refLevel = nullptr;
};