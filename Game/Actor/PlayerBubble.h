#pragma once

#include <Actor/DrawableActor.h>

class GameLevel;
class PlayerBubble : public DrawableActor
{
	RTTI_DECLARATIONS(PlayerBubble, DrawableActor)

public:
	// ź���� ������ �� ��ġ�� ���� �޾ƾ� ��.
	PlayerBubble(const Vector2& position, GameLevel* level);

	virtual void Update(float deltaTime) override;

	int bubbleDirection = 0;

private:
	// �̵� ���� ����.
	// �̵� �ӷ� (����: ĭ/��).
	float speed = 20.0f;

	float xPosition = 0.0f;
	float yPosition = 0.0f;

	GameLevel* refLevel = nullptr;
};