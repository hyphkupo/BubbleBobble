#pragma once

#include <Actor/DrawableActor.h>

class GameLevel;
class PlayerBubble : public DrawableActor
{
	RTTI_DECLARATIONS(PlayerBubble, DrawableActor)

public:
	// 탄약은 생성할 때 위치를 전달 받아야 함.
	PlayerBubble(const Vector2& position, int flag, GameLevel* level);

	virtual void Update(float deltaTime) override;

private:
	// 이동 관련 변수.
	// 이동 속력 (단위: 칸/초).
	float speed = 20.0f;

	float xPosition = 0.0f;
	float yPosition = 0.0f;

	// 플레이어의 버블 발사 방향 결정 값을 받아오는 변수
	int bubbleDirection = 0;

	GameLevel* refLevel;
};