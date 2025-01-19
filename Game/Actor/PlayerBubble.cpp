#include "PlayerBubble.h"
#include <cmath>

PlayerBubble::PlayerBubble(const Vector2& position)
	: DrawableActor("o")
{
	// ź�� ��ġ ����.
	this->position = position;
	yPosition = (float)position.y;
}

void PlayerBubble::Update(float deltaTime)
{
	Super::Update(deltaTime);

	// ��ġ ����.
	// ������ ���� �̵�.
	//--position.y;

	// ������ �ð��� ����� �̵�.
	yPosition -= speed * deltaTime;
	position.y = (int)yPosition;

	// y��ǥ�� ȭ���� ����� ���� ����.
	//if (position.y < 0)
	if (yPosition < 0.0f)
	{
		Destroy();
		return;
	}
}