#include "Enemy.h"
#include "Engine/Engine.h"
#include "Math/Vector2.h"
#include "Level/GameLevel.h"
#include "Actor/DrawableActor.h"

Enemy::Enemy(const char* image)
	: Super(image)
{
	// �� ���� ��ġ
	xPosition = Random(10, 21);
	position = Vector2(xPosition, 5);

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

void Enemy::Update(float deltaTime)
{
	Super::Update(deltaTime);

	// �¿� �̵�
	float factor = direction == Direction::Left ? -1.0f : 1.0f;
	xPosition += speed * factor * deltaTime;
	position.x = (int)xPosition;

	// ���� �� ����� �ݴ� �������� �̵�
	if (position.x < 10.0f || position.x > 21.0f)
	{
		factor *= (-1.0f);
		xPosition += speed * factor * deltaTime;
		position.x = (int)xPosition;
	}
	//xPosition += Random(-1, 1);
	//if (xPosition < 10.0f)
	//{
	//	position = Vector2(10, 5);
	//}

	//if (xPosition > 21.0f)
	//{
	//	//position.x = 21;
	//	position = Vector2(21, 5);

	//}
	//
	//position.x = (int)xPosition;

}

void Enemy::SetGravity()
{
	Vector2 newPosition = position;
	if (refLevel->IsInAir)
	{
		newPosition.y = 3;		// Ground �迭 �� ���� ����� ���� ��ġ
	}
}