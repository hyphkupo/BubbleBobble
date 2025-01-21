#include "PlayerBubble.h"
#include "Engine/Engine.h"
#include "Level/GameLevel.h"
#include <cmath>

PlayerBubble::PlayerBubble(const Vector2& position, GameLevel* level)
	: DrawableActor("o"), refLevel(level)
{
	color = Color::Yellow;

	// 버블 위치 설정
	this->position = position;
	xPosition = (float)position.x;
	yPosition = (float)position.y;

	//int bubbleDirection = 
}

void PlayerBubble::Update(float deltaTime)
{
	Super::Update(deltaTime);

	if (refLevel->flag == 0)		// LEFT
	{
		xPosition -= speed * deltaTime;
		position.x = (int)xPosition;
	}

	else if (refLevel->flag == 1)	// RIGHT
	{
		xPosition += speed * deltaTime;
		position.x = (int)xPosition;
	}

	else if (refLevel->flag == 2)	// UP
	{
		yPosition -= speed / 2 * deltaTime;
		position.y = (int)yPosition;
	}

	else if (refLevel->flag == 3)	// DOWN
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