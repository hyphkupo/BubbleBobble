#pragma once

#include <Actor/DrawableActor.h>

class PlayerBubble : public DrawableActor
{
	RTTI_DECLARATIONS(PlayerBubble, DrawableActor)

public:
	// ź���� ������ �� ��ġ�� ���� �޾ƾ� ��.
	PlayerBubble(const Vector2& position);

	virtual void Update(float deltaTime) override;

private:

	// �̵� ���� ����.
	// �̵� �ӷ� (����: ĭ/��).
	float speed = 20.0f;

	// y��ġ.
	float yPosition = 0.0f;
};