#include "Player.h"
#include "Engine/Engine.h"
#include "Math/Vector2.h"
#include "Level/GameLevel.h"
#include "Game/Game.h"
#include "Actor/PlayerBubble.h"

Player::Player(const char* image, GameLevel* level)
	: Super(image), refLevel(level)
{
	// 플레이어 시작 위치.
	position = Vector2(Engine::Get().ScreenSize().x/2 - 1, Engine::Get().ScreenSize().y - 5);
}

void Player::Update(float deltaTime)
{
	// 부모 함수 호출.
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

	// ESC 종료.
	if (Engine::Get().GetKeyDown(VK_ESCAPE))
	{
		//Engine::Get().QuitGame();
		// 메뉴 토글.
		Game::Get().ToggleMenu();
	}

	// 키 입력 처리.
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

	// 땅 위에 있거나 벽 위에 있을 때 스페이스 바를 누르면 점프
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
//	// 플레이어가 공중에 있으면
//	if (refLevel->IsInAir)
//	{
//		// 착지
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

//// 현재 위치 아래 중 가장 가까운 Ground 위치로 이동
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
//	//newPosition.y = 1;		// Ground 배열 중 가장 가까운 원소 위치
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