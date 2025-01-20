#include "Enemy2.h"
#include "Engine/Engine.h"
#include "Math/Vector2.h"
#include "Level/GameLevel.h"
#include "Actor/DrawableActor.h"

Enemy2::Enemy2(const char* image, int inputPositionY, GameLevel* level)
	: DrawableActor("a"), refLevel(level)
{
	// 적 시작 위치
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

	// 좌우 이동
	factor = direction == Direction::Left ? -1.0f : 1.0f;
	xPosition += speed * factor * deltaTime;
	position.x = (int)xPosition;

	// 범위 밖 벗어나면 반대 방향으로 이동
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
//		newPosition.y = 3;		// Ground 배열 중 가장 가까운 원소 위치
//	}
//}