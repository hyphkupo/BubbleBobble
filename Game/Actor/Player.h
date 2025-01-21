#pragma once

#include "Actor/DrawableActor.h"

class GameLevel;
class Player : public DrawableActor
{
	RTTI_DECLARATIONS(Player, DrawableActor)

public:
	Player(const char* image, GameLevel* level);

	virtual void Update(float deltaTime) override;

	int flag = 0;

private:
	float xPosition = 0.0f;
	float yPosition = 0.0f;
	float speed = 5.0f;

	GameLevel* refLevel = nullptr;
};