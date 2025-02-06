#include "Enemy.h"
#include "Engine/Engine.h"
#include "Math/Vector2.h"
#include "Level/GameLevel.h"
#include "Actor/DrawableActor.h"

Enemy::Enemy(const char* image, int x, int y, int inputPositionY, GameLevel* level)
	: DrawableActor("a"), minX(x), maxX(y), refLevel(level)
{
	if (refLevel->stageNumber == 1)
	{
		// �� ���� ��ġ
		xPosition = Random(minX, maxX);
		position = Vector2(xPosition, inputPositionY);
		yPosition = (float)position.y;
	}

	else if (refLevel->stageNumber == 2)
	{
		// �� ���� ��ġ
		xPosition = Random(minX, maxX);
		position = Vector2(xPosition, inputPositionY);
		yPosition = (float)position.y;
	}

	else if (refLevel->stageNumber == 3)
	{
		// �� ���� ��ġ
		speed = 6.0f;
		RedrawImage("*", Color::White);
		yPosition = Random(minX, maxX);
		position = Vector2(inputPositionY, yPosition);
		xPosition = (float)position.x;
	}

	int random = Random(1, 10);
	random %= 2;
	
	if (random)
	{
		direction = Direction::Left;
	}

	else
	{
		direction = Direction::Right;
	}

	factor = direction == Direction::Left ? -1.0f : 1.0f;
}

void Enemy::Update(float deltaTime)
{
	Super::Update(deltaTime);

	// ���� ������ ���� ���¶�� �� --y
	if (inBubble)
	{
		MoveInBubble(deltaTime);
	}

	// ���� ������ ���� ���� ����
	else
	{
		MoveEnemy(deltaTime);
	}
}

void Enemy::SetPosition(const Vector2& newPosition)
{
	Super::SetPosition(newPosition);
}

void Enemy::MoveEnemy(float deltaTime)
{
	// Stage3
	if (refLevel->stageNumber == 4)
	{
		// ���� �̵�
		yPosition += speed * factor * deltaTime;
		position.y = (int)yPosition;

		// ���� ����� �ݴ� �������� �̵�
		if (position.y < minX || position.y > maxX)
		{
			factor *= (-1.0f);
			yPosition += speed * factor * deltaTime;
			position.y = (int)yPosition;
		}
	}
	
	else
	{
		// �¿� �̵�
		xPosition += speed * factor * deltaTime;
		position.x = (int)xPosition;

		// ���� ����� �ݴ� �������� �̵�
		if (position.x < minX || position.x > maxX)
		{
			factor *= (-1.0f);
			xPosition += speed * factor * deltaTime;
			position.x = (int)xPosition;
		}
	}
}

// ���� ������ ���� ���¶�� �� --y
void Enemy::MoveInBubble(float deltaTime)
{
	yPosition -= speed / 2 * deltaTime;
	position.y = (int)yPosition;

	if (position.y < 0)
	{
		Destroy();
		return;
	}
}