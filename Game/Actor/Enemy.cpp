#include "Enemy.h"
#include "Engine/Engine.h"
#include "Math/Vector2.h"
#include "Level/GameLevel.h"
#include "Actor/DrawableActor.h"

Enemy::Enemy(const char* image)
	: Super(image)
{
	// 적 시작 위치
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

	// 좌우 이동
	float factor = direction == Direction::Left ? -1.0f : 1.0f;
	xPosition += speed * factor * deltaTime;
	position.x = (int)xPosition;

	// 범위 밖 벗어나면 반대 방향으로 이동
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
		newPosition.y = 3;		// Ground 배열 중 가장 가까운 원소 위치
	}
}