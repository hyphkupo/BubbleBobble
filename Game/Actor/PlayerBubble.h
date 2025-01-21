#pragma once

#include <Actor/DrawableActor.h>

class GameLevel;
class PlayerBubble : public DrawableActor
{
	RTTI_DECLARATIONS(PlayerBubble, DrawableActor)

public:
	// 탄약은 생성할 때 위치를 전달 받아야 함.
	PlayerBubble(const Vector2& position, GameLevel* level);

	virtual void Update(float deltaTime) override;

	int bubbleDirection = 0;

private:
	// 이동 관련 변수.
	// 이동 속력 (단위: 칸/초).
	float speed = 20.0f;

	float xPosition = 0.0f;
	float yPosition = 0.0f;

	GameLevel* refLevel = nullptr;
};