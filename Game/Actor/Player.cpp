#include "Player.h"
#include "Engine/Engine.h"
#include "Math/Vector2.h"
#include "Level/GameLevel.h"

Player::Player(const char* image, GameLevel* level)
	: Super(image), refLevel(level)
{
	// 플레이어 시작 위치.
	position = Vector2(Engine::Get().ScreenSize().x/2 - 1, Engine::Get().ScreenSize().y - 2);
}

void Player::Update(float deltaTime)
{
	// 부모 함수 호출.
	Super::Update(deltaTime);

	// 키 입력 처리.
	if (Engine::Get().GetKey(VK_LEFT))
	{
		Vector2 newPosition = position;
		--newPosition.x;
		if (newPosition.x < 0)
		{
			newPosition.x = 0;
		}

		SetPosition(newPosition);
	}

	if (Engine::Get().GetKey(VK_RIGHT))
	{
		Vector2 newPosition = position;
		++newPosition.x;
		if (newPosition.x > Engine::Get().ScreenSize().x - width)
		{
			newPosition.x = Engine::Get().ScreenSize().x - width;
		}

		SetPosition(newPosition);
	}

	// 땅 위에 있거나 벽 위에 있을 때 스페이스 바를 누르면 점프
	if (Engine::Get().GetKey(VK_SPACE) && (refLevel->IsOnGround || refLevel->IsOnWall))
	{
		Vector2 newPosition = position;
		//newPosition.y -= speed * deltaTime;
		newPosition.y -= 4;

		if (newPosition.y < 0)
		{
			newPosition.y = 0;
		}

		SetPosition(newPosition);
		refLevel->IsInAir = true;
	}

	// 착지
	if (refLevel->IsInAir)
	{
		Vector2 newPosition = position;
		newPosition.y += 3;

		if (newPosition.y > Engine::Get().ScreenSize().y - width)
		{
			newPosition.y = Engine::Get().ScreenSize().y - width;
		}

		SetPosition(newPosition);
		refLevel->IsInAir = false;
	}
}

void Player::SetGravity()
{
	Vector2 newPosition = position;
	if (refLevel->IsInAir)
	{
		newPosition.y = 1;		// Ground 배열 중 가장 가까운 원소 위치
	}
}