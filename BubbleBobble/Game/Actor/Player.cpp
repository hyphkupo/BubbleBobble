#include "Player.h"
#include "Engine/Engine.h"
#include "Math/Vector2.h"
#include "Level/GameLevel.h"
#include "Game/Game.h"
#include "Actor/PlayerBubble.h"

Player::Player(const char* image, GameLevel* level)
	: Super(image), refLevel(level)
{
	// �÷��̾� ���� ��ġ.
	position = Vector2(Engine::Get().ScreenSize().x/2 - 1, Engine::Get().ScreenSize().y - 5);
}

void Player::Update(float deltaTime)
{
	// �θ� �Լ� ȣ��.
	Super::Update(deltaTime);

	//if (position.y < 1)
	//{
	//	position.y = 1;
	//}

	//if (position.y == 1)
	//{
	//	position.y = 2;
	//}

	//if (position.y == 4)
	//{
	//	position.y = 5;
	//}

	//if (position.y == 7)
	//{
	//	position.y = 8;
	//}

	//if (position.x == 5 && position.y == )

	//if (position.y == 11)
	//{
	//	Engine::Get().QuitGame();
	//}

	//if (refLevel->IsOnGround(position))
	//{
	//	position.y++;
	//}

	// ESC ����.
	if (Engine::Get().GetKeyDown(VK_ESCAPE))
	{
		//Engine::Get().QuitGame();
		// �޴� ���.
		Game::Get().ToggleMenu();
	}

	// Ű �Է� ó��.
	if (Engine::Get().GetKey(VK_LEFT))
	{
		if (refLevel->CanPlayerMove(Vector2(position.x - 1, position.y)))
		{
			--position.x;

			if (position.x < 0)
			{
				position.x = 0;
			}
		}
	}

	if (Engine::Get().GetKey(VK_RIGHT))
	{
		if (refLevel->CanPlayerMove(Vector2(position.x + 1, position.y)))
		{
			++position.x;

			if (position.x > Engine::Get().ScreenSize().x - width)
			{
				position.x = Engine::Get().ScreenSize().x - width;
			}
		}

		//Vector2 newPosition = position;
		//++newPosition.x;
		//if (newPosition.x > Engine::Get().ScreenSize().x - width)
		//{
		//	newPosition.x = Engine::Get().ScreenSize().x - width;
		//}

		//SetPosition(newPosition);
	}

	if (Engine::Get().GetKey(VK_UP))
	{
		if (refLevel->CanPlayerMove(Vector2(position.x, position.y - 1)))
		{
			--position.y;

			if (position.y < 1)
			{
				position.y = 1;
			}
		}
	}

	if (Engine::Get().GetKey(VK_DOWN))
	{
		if (refLevel->CanPlayerMove(Vector2(position.x, position.y + 1)))
		{
			++position.y;

			if (position.y > 10)
			{
				position.y = 10;
			}
		}
	}

	if (Engine::Get().GetKeyDown(VK_TAB))
	{
		Vector2 bubblePosition(position.x + (width / 2), position.y);
		Engine::Get().AddActor(new PlayerBubble(bubblePosition));
	}

	// �� ���� �ְų� �� ���� ���� �� �����̽� �ٸ� ������ ����
//	if (Engine::Get().GetKey(VK_SPACE) && (refLevel->IsOnGround(Vector2(position.x, position.y + 1))))
//	{
//		//Vector2 newPosition = position;
//		//newPosition.y -= 2;
//		position.y -= 3;
//
//		if (position.y < 0)
//		{
//			position.y = 1;
//		}
//
//		//SetPosition(newPosition);
//
//		refLevel->IsInAir = true;
//	}
//
//	// �÷��̾ ���߿� ������
//	if (refLevel->IsInAir)
//	{
//		// ����
//		//SetGravity();
//
//		//Vector2 newPosition = position;
//		//newPosition.y += 3;
//
//		//if (newPosition.y > Engine::Get().ScreenSize().y - width)
//		//{
//		//	newPosition.y = Engine::Get().ScreenSize().y - width;
//		//}
//
//		//SetPosition(newPosition);
//
//		refLevel->IsInAir = false;
//	}
//}

//// ���� ��ġ �Ʒ� �� ���� ����� Ground ��ġ�� �̵�
//void Player::SetGravity()
//{
//	//Vector2 newPosition = position;
//	Vector2 isGround = position;
//
//	while (isGround.y > 1)
//	{
//		if (refLevel->IsOnGround(Vector2(isGround.x, isGround.y)))
//		{
//			position.y = isGround.y - 1;
//			//SetPosition(newPosition);
//			break;
//		}
//		else
//		{
//			++isGround.y;
//		}
//	}
//
//
//	//newPosition.y = 1;		// Ground �迭 �� ���� ����� ���� ��ġ
//	//newPosition.y += 3;
//
//	if (position.y > Engine::Get().ScreenSize().y - width)
//	{
//		position.y = Engine::Get().ScreenSize().y - width;
//	}
//
//	if (position.y < 1)
//	{
//		position.y = 1;
//	}
}