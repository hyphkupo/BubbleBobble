#include "Enemy.h"
#include "Engine/Engine.h"
#include "Math/Vector2.h"
#include "Level/GameLevel.h"

Enemy::Enemy(const char* image)
	: Super(image)
{
	// 적 시작 위치.
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

	// 좌우 이동
	float factor = direction == Direction::Left ? -1.0f : 1.0f;
	xPosition += speed * factor * deltaTime;
	position.x = (int)xPosition;

	// 범위 밖 벗어나면 반대 방향으로 이동
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
		newPosition.y = 1;		// Ground 배열 중 가장 가까운 원소 위치
	}
}