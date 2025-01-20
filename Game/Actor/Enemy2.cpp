#include "Enemy2.h"
#include "Engine/Engine.h"
#include "Math/Vector2.h"
#include "Level/GameLevel.h"
#include "Actor/DrawableActor.h"

Enemy2::Enemy2(const char* image, int inputPositionY, GameLevel* level)
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
}

void Enemy2::Update(float deltaTime)
{
	Super::Update(deltaTime);

	// �¿� �̵�
	factor = direction == Direction::Left ? -1.0f : 1.0f;
	xPosition += speed * factor * deltaTime;
	position.x = (int)xPosition;

	// ���� �� ����� �ݴ� �������� �̵�
	if (position.x < 10.0f || position.x > 21.0f)
	{
		factor *= (-1.0f);
		xPosition += speed * factor * deltaTime;
		position.x = (int)xPosition;
	}

	//if (refLevel->inBubble)
	//{
	//	yPosition = position.y;
	//	yPosition -= speed / 100 * deltaTime;
	//	position.y = (int)yPosition;
	//	if (position.y < 1)
	//	{
	//		Destroy();
	//		return;
	//	}
	//}
}

void Enemy2::SetPosition(const Vector2& newPosition)
{
	Super::SetPosition(newPosition);
}

//void Enemy::SetGravity()
//{
//	Vector2 newPosition = position;
//	if (refLevel->IsInAir)
//	{
//		newPosition.y = 3;		// Ground �迭 �� ���� ����� ���� ��ġ
//	}
//}