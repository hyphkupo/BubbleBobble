#pragma once

#include "Actor/DrawableActor.h"

class Enemy : public DrawableActor
{
	// 적 캐릭터가 이동할 방향.
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

private:
	Direction direction = Direction::None;
	float xPosition = 0.0f;
	float speed = 5.0f;
};