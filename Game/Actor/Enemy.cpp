#include "Enemy.h"
#include "Engine/Engine.h"
#include "Math/Vector2.h"
#include "Level/GameLevel.h"
#include "Actor/DrawableActor.h"
#include "Engine/Timer.h"

Enemy::Enemy(const char* image, int inputPositionY, GameLevel* level)
	: DrawableActor("a"), refLevel(level)
{
	// �� ���� ��ġ
	xPosition = Random(10, 21);
	position = Vector2(xPosition, inputPositionY);

	int random = Random(1, 10);
	random %= 2;
	
	if (random)
	{
		direction = Direction::Left;
		//xPosition = 21.0f;
	}
	else
	{
		direction = Direction::Right;
		//xPosition = 10.0f;
	}

	factor = direction == Direction::Left ? -1.0f : 1.0f;
	yPosition = (float)position.y;
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
	// �¿� �̵�
	xPosition += speed * factor * deltaTime;
	position.x = (int)xPosition;

	// ���� ����� �ݴ� �������� �̵�
	if (position.x < 9.0f || position.x > 22.0f)
	{
		factor *= (-1.0f);
		xPosition += speed * factor * deltaTime;
		position.x = (int)xPosition;
	}
}

// ���� ������ ���� ���¶�� �� --y
void Enemy::MoveInBubble(float deltaTime)
{
	//xPosition += Random(-2, 2) * speed / 2 * deltaTime;
	//position.x = (int)xPosition;

	yPosition -= speed / 2 * deltaTime;
	position.y = (int)yPosition;

	if (position.y < 1)
	{
		Destroy();
		return;
	}
}

//void Enemy::SetGravity()
//{
//	Vector2 newPosition = position;
//	if (refLevel->IsInAir)
//	{
//		newPosition.y = 3;		// Ground �迭 �� ���� ����� ���� ��ġ
//	}
//}