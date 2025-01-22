#include "Player.h"
#include "Engine/Engine.h"
#include "Math/Vector2.h"
#include "Level/GameLevel.h"
#include "Game/Game.h"
#include "Actor/PlayerBubble.h"

Player::Player(const char* image, GameLevel* level)
	: DrawableActor("P"), refLevel(level)
{
	color = Color::MoreGreen;

	if (refLevel->stageNumber == 1)
	{
		// 플레이어 시작 위치
		position = Vector2(Engine::Get().ScreenSize().x / 2 - 1, Engine::Get().ScreenSize().y - 12);
	}

	else if (refLevel->stageNumber == 2)
	{
		// 플레이어 시작 위치
		position = Vector2(Engine::Get().ScreenSize().x / 2 - 1, Engine::Get().ScreenSize().y - 4);
	}

	else if (refLevel->stageNumber == 3)
	{
		// 플레이어 시작 위치
		position = Vector2(Engine::Get().ScreenSize().x / 2 - 1, Engine::Get().ScreenSize().y - 12);
	}
	
	xPosition = position.x;
	yPosition = position.y;
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
			//--position.x;
			xPosition -= speed * 3 * deltaTime;
			position.x = (int)xPosition;

			if (position.x < 0)
			{
				position.x = 0;
			}
		}

		//if (!refLevel->isBubbleMoving)
		//{
		//	refLevel->flag = 0;
		//}

		flag = 0;
	}

	if (Engine::Get().GetKey(VK_RIGHT) || Engine::Get().GetKey(VK_D))
	{
		if (refLevel->CanPlayerMove(Vector2(position.x + 1, position.y)))
		{
			//++position.x;
			xPosition += speed * 3 * deltaTime;
			position.x = (int)xPosition;

			if (position.x > Engine::Get().ScreenSize().x - width)
			{
				position.x = Engine::Get().ScreenSize().x - width;
			}
		}

		flag = 1;
	}

	if (Engine::Get().GetKey(VK_UP) || Engine::Get().GetKey(VK_W))
	{
		if (refLevel->CanPlayerMove(Vector2(position.x, position.y - 1)))
		{
			//--position.y;
			yPosition -= speed * 2 * deltaTime;
			position.y = (int)yPosition;

			if (position.y < 1)
			{
				position.y = 1;
			}
		}

		flag = 2;
	}

	if (Engine::Get().GetKey(VK_DOWN) || Engine::Get().GetKey(VK_S))
	{
		if (refLevel->CanPlayerMove(Vector2(position.x, position.y + 1)))
		{
			//++position.y;
			yPosition += speed * 2 * deltaTime;
			position.y = (int)yPosition;

			if (position.y > 10)
			{
				position.y = 10;
			}
		}

		flag = 3;
	}

	if (Engine::Get().GetKeyDown(VK_SPACE))
	{
		Vector2 bubblePosition(position.x + (width / 2), position.y);

		Engine::Get().AddActor(new PlayerBubble(bubblePosition, flag, refLevel));
	}
}