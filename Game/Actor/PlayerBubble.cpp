#include "PlayerBubble.h"
#include "Engine/Engine.h"
#include "Level/GameLevel.h"
#include <cmath>

PlayerBubble::PlayerBubble(const Vector2& position, int flag)
	: DrawableActor("o")
{
	color = Color::Yellow;

	// 버블 위치 설정
	this->position = position;
	xPosition = (float)position.x;
	yPosition = (float)position.y;

	bubbleDirection = flag;
}

void PlayerBubble::Update(float deltaTime)
{
	Super::Update(deltaTime);

	// 버블 방향 처리
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

	// Wall에 버블이 부딪히면 destroy
	if (xPosition < 1.0f)
	{
		xPosition = 1.0f;
		//refLevel->isBubbleMoving = false;
		this->Destroy();
		return;
	}

	if (position.x > Engine::Get().ScreenSize().x - 1)
	{
		position.x = Engine::Get().ScreenSize().x - 1;
		//refLevel->isBubbleMoving = false;
		this->Destroy();
		return;
	}

	if (yPosition < 1.0f)
	{
		yPosition = 1.0f;
		//refLevel->isBubbleMoving = false;
		this->Destroy();
		return;
	}

	if (yPosition > 10.0f)
	{
		yPosition = 10.0f;
		//refLevel->isBubbleMoving = false;
		this->Destroy();
		return;
	}

	// Ground에 버블이 부딪히면 destroy
	if (position.y == 2 || position.y == 5 || position.y == 8)
	{
		if ((1 <= position.x && position.x <= 4) || (9 <= position.x && position.x <= 22) || (27 <= position.x && position.x <= 30))
		{
			this->Destroy();
			//refLevel->isBubbleMoving = false;
			return;
		}
	}
}