#include "Enemy.h"
#include "Engine/Engine.h"
#include "Math/Vector2.h"
#include "Level/GameLevel.h"

Enemy::Enemy(const char* image)
	: Super(image)
{
	// �� ���� ��ġ.
	position = Vector2(Random(10, 23), 7);

	int random = Random(1, 10);
	random %= 2;
	if (random)
	{
		direction = Direction::Left;
		//xPosition = 23;
	}
	else
	{
		direction = Direction::Right;
		//xPosition = 10;
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
	if (xPosition < 10.0f || xPosition > 23.0f)
	{
		factor *= (-1.0f);
		xPosition += speed * factor * deltaTime;
		position.x = (int)xPosition;
	}
}

void Enemy::SetGravity()
{
	Vector2 newPosition = position;
	if (refLevel->IsInAir)
	{
		newPosition.y = 1;		// Ground �迭 �� ���� ����� ���� ��ġ
	}
}