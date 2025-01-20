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

	//List<PlayerBubble*> shootBubble;

private:
	float speed = 5.0f;

	GameLevel* refLevel = nullptr;
};