#include "PlayerBubble.h"
#include "Engine/Engine.h"
#include "Level/GameLevel.h"
#include <cmath>

PlayerBubble::PlayerBubble(const Vector2& position, int flag, GameLevel* level)
	: DrawableActor("o"), refLevel(level)
{
	color = Color::Yellow;

	// ���� ��ġ ����
	this->position = position;
	xPosition = (float)position.x;
	yPosition = (float)position.y;

	bubbleDirection = flag;
}

void PlayerBubble::Update(float deltaTime)
{
	Super::Update(deltaTime);

	// ���� ���� ó��
	if (bubbleDirection == 0)		// LEFT
	{
		xPosition -= speed * deltaTime;
		position.x = (int)xPosition;
	}

	else if (bubbleDirection == 1)	// RIGHT
	{
		xPosition += speed * deltaTime;
		position.x = (int)xPosition;
	}

	else if (bubbleDirection == 2)	// UP
	{
		yPosition -= speed / 2 * deltaTime;
		position.y = (int)yPosition;
	}

	else if (bubbleDirection == 3)	// DOWN
	{
		yPosition += speed / 2 * deltaTime;
		position.y = (int)yPosition;
	}

	// Wall�� ������ �ε����� destroy
	if (xPosition < 1.0f)
	{
		xPosition = 1.0f;
		this->Destroy();
		return;
	}

	if (position.x > Engine::Get().ScreenSize().x - 2)
	{
		position.x = Engine::Get().ScreenSize().x - 2;
		this->Destroy();
		return;
	}

	if (yPosition < 1.0f)
	{
		yPosition = 1.0f;
		this->Destroy();
		return;
	}

	if (yPosition > 10.0f)
	{
		yPosition = 10.0f;
		this->Destroy();
		return;
	}

	// Ground�� ������ �ε����� destroy
	if (refLevel->isGround(position))
	{
		this->Destroy();
		return;
	}
}