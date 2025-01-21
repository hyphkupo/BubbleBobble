#include "GameLevel.h"
#include "Engine/Engine.h"
#include "Actor/Wall.h"
#include "Actor/Ground.h"
#include "Actor/Air.h"

#include "Actor/Player.h"
#include "Actor/Enemy.h"
#include "Actor/PlayerBubble.h"

#include <Windows.h>
#include "Game/Game.h"

GameLevel::GameLevel()
{
	// Ŀ�� ���߱�.
	Engine::Get().SetCursorType(CursorType::NoCursor);

	// �� ���� �ҷ��� ���� �ε�.
	// ���� �б�.
	FILE* file = nullptr;

	fopen_s(&file, "../Assets/Maps/Stage1.txt", "rb");

	// ���� ó��.
	if (file == nullptr)
	{
		std::cout << "�� ���� ���� ����.\n";
		__debugbreak();
		return;
	}

	// ���� �б�.
	// ����ġ�� �̵�.
	fseek(file, 0, SEEK_END);

	// �̵��� ��ġ�� FP ��������.
	size_t readSize = ftell(file);

	// FP ����ġ.
	rewind(file);

	// ���� �о ���ۿ� ���.
	char* buffer = new char[readSize + 1];
	size_t bytesRead = fread(buffer, 1, readSize, file);

	if (readSize != bytesRead)
	{
		std::cout << "�о�� ũ�Ⱑ �ٸ�\n";
		__debugbreak();
		return;
	}

	buffer[readSize] = '\0';

	// ���� ���� �� ����� �ε���.
	int index = 0;

	// ��ǥ ����� ���� ���� ����.
	int xPosition = 0;
	int yPosition = 0;

	// �ؼ� (�Ľ�-Parcing).
	while (index < (int)bytesRead)
	{
		// �� ���ھ� �б�.
		char mapChar = buffer[index++];

		// ���� ������ ��� ó��.
		if (mapChar == '\n')
		{
			++yPosition;
			xPosition = 0;
			continue;
		}

		// �� ���ڰ� 1�̸� Wall ���� ����
		if (mapChar == '1')
		{
			Wall* wall = new Wall(Vector2(xPosition, yPosition));
			actors.PushBack(wall);
			map.PushBack(wall);
		}

		// �� ���ڰ� 0�̸� �׶��� ���� ����
		else if (mapChar == '0')
		{
			Ground* ground = new Ground(Vector2(xPosition, yPosition));
			actors.PushBack(ground);
			map.PushBack(ground);
		}

		else if (mapChar == '.')
		{
			Air* air = new Air(Vector2(xPosition, yPosition));
			actors.PushBack(air);
			map.PushBack(air);
		}

		++xPosition;
	}

	AddActor(new Player("p", this));
	AddActor(new Enemy("x", 4, this));
	AddActor(new Enemy("x", 7, this));
	//AddActor(new Enemy2("x", 4, this));

	delete[] buffer;

	fclose(file);
}

void GameLevel::Update(float deltaTime)
{
	Super::Update(deltaTime);

	// ���� ó��.
	if (deltaTime > 1.0f)
	{
		return;
	}

	// ESC Ű�� ����.
	//if (Engine::Get().GetKeyDown(VK_ESCAPE))
	//{
	//	Game::Get().ToggleMenu();
	//}

	// Wall �Ǵ� Ground�� �ƴϸ� IsInAir = true

	// �÷��̾� ����� ���� �浹 ó��.
	ProcessCollisionPlayerBubbleAndEnemy();

	// ���� �÷��̾��� �浹 ó��.
	ProcessCollisionPlayerAndEnemy();
}

void GameLevel::Draw()
{
	Super::Draw();

	if (isPlayerDead)
	{
		int y = Engine::Get().ScreenSize().y;
		Engine::Get().Draw(Vector2(Engine::Get().ScreenSize().x - 10, Engine::Get().ScreenSize().y - 1), "Game Over!");
		//Engine::Get().Present();

		Sleep(3000);

		Engine::Get().QuitGame();
	}

	else if (CheckGameClear())
	{
		int y = Engine::Get().ScreenSize().y;
		Engine::Get().Draw(Vector2(Engine::Get().ScreenSize().x - 11, Engine::Get().ScreenSize().y - 1), "Game Clear!");
		//Engine::Get().Present();

		Sleep(3000);

		Engine::Get().QuitGame();
	}

	// ���� ���.
	char buffer[256];
	snprintf(buffer, 256, "Score: %d", score);
	Engine::Get().Draw(Vector2(0, Engine::Get().ScreenSize().y - 1), buffer);
}

// �÷��̾��� ����� �� �浹 ó��
void GameLevel::ProcessCollisionPlayerBubbleAndEnemy()
{
	// ���� �� �� ĳ���� �迭 ����.
	List<PlayerBubble*> bubbles;
	List<Enemy*> enemies;
	Player* player = nullptr;

	// ������ ��ġ�� ���͸� ��ȸ�ϸ鼭 ����Ʈ ä���.
	for (Actor* actor : actors)
	{
		// �÷��̾ �������� �ʾ����� �÷��̾�� ����ȯ.
		if (!player)
		{
			player = actor->As<Player>();
			continue;
		}

		// ����ȯ �� Ȯ���ؼ� ����Ʈ ä���.
		PlayerBubble* bubble = actor->As<PlayerBubble>();
		if (bubble)
		{
			bubbles.PushBack(bubble);
			continue;
		}

		// ������ ����ȯ �� Ȯ���ؼ� ����Ʈ ä���.
		Enemy* enemy = actor->As<Enemy>();
		if (enemy)
		{
			enemies.PushBack(enemy);
		}
	}

	// ���� ó��.
	if (bubbles.Size() == 0 || enemies.Size() == 0)
	{
		return;
	}

	// �� �迭�� ��ȸ�ϸ鼭 �浹 ó��.
	for (PlayerBubble* bubble : bubbles)
	{
		for (Enemy* enemy : enemies)
		{
			// ���� ��Ȱ��ȭ ���¶�� �ǳʶٱ�.
			if (!enemy->IsActive())
			{
				continue;
			}

			// �浹 ó��.
			if (enemy->Intersect(*bubble))
			{
				//inBubble = true;
				enemy->inBubble = true;

				if (enemy->inBubble)
				{
					enemy->RedrawImage("@", Color::Yellow);
					
				}

				// �� ������ ����� �� ����
				if (enemy->Position().y < 1)
				{
					enemy->Destroy();
				}

				// ���� ����
				bubble->Destroy();
			}
		}
	}
}

// �÷��̾�� �� �浹 ó��
void GameLevel::ProcessCollisionPlayerAndEnemy()
{
	// ź�� �� �� ĳ���� �迭 ����.
	List<Enemy*> enemies;
	Player* player = nullptr;

	// ���� ����� ��ȸ�ϸ鼭 ź��� �� ĳ���͸� ã�� �迭�� �߰�.
	for (Actor* actor : actors)
	{
		// �÷��̾ �������� �ʾ����� �÷��̾�� ����ȯ.
		if (!player)
		{
			player = actor->As<Player>();
			continue;
		}

		// ������ ����ȯ �����ϸ� ��Ͽ� �߰�.
		Enemy* enemy = actor->As<Enemy>();
		if (enemy)
		{
			enemies.PushBack(enemy);
		}
	}

	// �÷��̾ ��ã�Ұų� �� ź���� ������ �浹 ó������ �ʰ� ����.
	if (player == nullptr || enemies.Size() == 0)
	{
		return;
	}

	// �� �迭�� ��ȸ�ϸ鼭 �浹 ó��.
	for (Enemy* enemy : enemies)
	{
		// �÷��̾ ��Ȱ��ȭ �����̸� �ǳʶٱ�.
		if (!player->IsActive())
		{
			continue;
		}

		// �÷��̾�� ���� �浹�ߴ��� Ȯ��
		if (player->Intersect(*enemy) && !enemy->inBubble)
		{
			isPlayerDead = true;
			//playerDeadPosition = Vector2(player->Position().x + player->Width() / 2, player->Position().y);
			player->Destroy();
		}

		// ���� �÷��̾�� ������ ���� �� �÷��̾�� �ε����ٸ� ���� �߰�, �� ����
		if (player->Intersect(*enemy) && enemy->inBubble)
		{
			score += 100;
			enemy->Destroy();
		}
	}
}

//void GameLevel::SpawnEnemy(float deltaTime)
//{
//	AddActor(new Enemy("x", 4, this));
//	AddActor(new Enemy("x", 7, this));
//}

bool GameLevel::CheckGameClear()
{
	List<Enemy*> enemies;

	for (Actor* actor : actors)
	{
		// ������ ����ȯ �����ϸ� ��Ͽ� �߰�.
		Enemy* enemy = actor->As<Enemy>();
		if (enemy)
		{
			return false;
		}
	}

	return true;
}

bool GameLevel::CanPlayerMove(const Vector2& position)
{
	// ������ Ŭ����� ��� �ٷ� ����.
	if (isGameClear)
	{
		return false;
	}

	// �̵��Ϸ��� ��ġ�� ���� �ִ��� Ȯ��.
	DrawableActor* searchedActor = nullptr;

	// ���� �̵��Ϸ��� ��ġ�� ���� ã��.
	for (auto* actor : map)
	{
		if (actor->Position() == position)
		{
			searchedActor = actor;
			break;
		}
	}

	// �˻��� ���Ͱ� ������ Ȯ��.
	if (searchedActor->As<Wall>())
	{
		return false;
	}

	// �˻��� ���Ͱ� �̵� ������ ����(��/Ÿ��)���� Ȯ��.
	if (searchedActor->As<Ground>())
	{
		return false;
	}

	return true;
}

//bool GameLevel::IsOnGround(const Vector2& position)
//{
//	// �̵��Ϸ��� ��ġ�� ���� �ִ��� Ȯ��.
//	Actor* searchedActor = nullptr;
//
//	// ���� �̵��Ϸ��� ��ġ�� ���� ã��.
//	for (auto* actor : actors)
//	{
//		if (actor->Position() == position)
//		{
//			searchedActor = actor;
//			break;
//		}
//	}
//
//	if (searchedActor->As<Ground>())
//	{
//		return true;
//	}
//
//	return false;
//}