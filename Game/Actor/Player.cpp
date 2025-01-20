#include "Player.h"
#include "Engine/Engine.h"
#include "Math/Vector2.h"
#include "Level/GameLevel.h"
#include "Game/Game.h"
#include "Actor/PlayerBubble.h"

Player::Player(const char* image, GameLevel* level)
	: Super(image), refLevel(level)
{
	// 플레이어 시작 위치
	position = Vector2(Engine::Get().ScreenSize().x/2 - 1, Engine::Get().ScreenSize().y - 6);
}

void Player::Update(float deltaTime)
{
	Super::Update(deltaTime);

	if (Engine::Get().GetKeyDown(VK_ESCAPE))
	{
		Engine::Get().QuitGame();
		// 메뉴 토글
		//Game::Get().ToggleMenu();
	}

	if (Engine::Get().GetKey(VK_LEFT) || Engine::Get().GetKey(VK_A))
	{
		if (refLevel->CanPlayerMove(Vector2(position.x - 1, position.y)))
		{
			--position.x;

			if (position.x < 0)
			{
				position.x = 0;
			}
		}

		//if (!refLevel->isBubbleMoving)
		//{
		//	refLevel->flag = 0;
		//}

		refLevel->flag = 0;
	}

	if (Engine::Get().GetKey(VK_RIGHT) || Engine::Get().GetKey(VK_D))
	{
		if (refLevel->CanPlayerMove(Vector2(position.x + 1, position.y)))
		{
			++position.x;

			if (position.x > Engine::Get().ScreenSize().x - width)
			{
				position.x = Engine::Get().ScreenSize().x - width;
			}
		}

		refLevel->flag = 1;
	}

	if (Engine::Get().GetKey(VK_UP) || Engine::Get().GetKey(VK_W))
	{
		if (refLevel->CanPlayerMove(Vector2(position.x, position.y - 1)))
		{
			--position.y;

			if (position.y < 1)
			{
				position.y = 1;
			}
		}

		refLevel->flag = 2;
	}

	if (Engine::Get().GetKey(VK_DOWN) || Engine::Get().GetKey(VK_S))
	{
		if (refLevel->CanPlayerMove(Vector2(position.x, position.y + 1)))
		{
			++position.y;

			if (position.y > 10)
			{
				position.y = 10;
			}
		}

		refLevel->flag = 3;
	}

	if (Engine::Get().GetKeyDown(VK_SPACE))
	{
		Vector2 bubblePosition(position.x + (width / 2), position.y);

		Engine::Get().AddActor(new PlayerBubble(bubblePosition, refLevel));
	}
}