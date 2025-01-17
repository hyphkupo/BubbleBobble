#include "Player.h"
#include "Engine/Engine.h"
#include "Math/Vector2.h"
#include "Level/GameLevel.h"

Player::Player(const char* image, GameLevel* level)
	: Super(image), refLevel(level)
{
	// �÷��̾� ���� ��ġ.
	position = Vector2(Engine::Get().ScreenSize().x/2 - 1, Engine::Get().ScreenSize().y - 2);
}

void Player::Update(float deltaTime)
{
	// �θ� �Լ� ȣ��.
	Super::Update(deltaTime);

	// Ű �Է� ó��.
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

	// �� ���� �ְų� �� ���� ���� �� �����̽� �ٸ� ������ ����
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

	// ����
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
		newPosition.y = 1;		// Ground �迭 �� ���� ����� ���� ��ġ
	}
}