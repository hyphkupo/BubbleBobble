#pragma once

#include "Actor/DrawableActor.h"

class GameLevel;
class Player : public DrawableActor
{
	RTTI_DECLARATIONS(Player, DrawableActor)

public:
	Player(const char* image, GameLevel* level);

	virtual void Update(float deltaTime) override;

	void SetGravity();


private:
	float speed = 5.0f;
	//float yPosition = 0.0f;

	GameLevel* refLevel = nullptr;
};