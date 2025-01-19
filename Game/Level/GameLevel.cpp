#include "GameLevel.h"
#include "Engine/Engine.h"
#include "Actor/Player.h"
#include "Actor/Wall.h"
#include "Actor/Ground.h"
#include "Actor/Air.h"

#include "Actor/Enemy.h"

#include <Windows.h>
#include "Game/Game.h"

//struct enemyType
//{
//
//};

// 적 캐릭터 종류.

GameLevel::GameLevel()
{
	// 커서 감추기.
	Engine::Get().SetCursorType(CursorType::NoCursor);

	// 맵 파일 불러와 레벨 로드.
	// 파일 읽기.
	FILE* file = nullptr;
	fopen_s(&file, "../Assets/Maps/Map.txt", "rb");

	// 파일 처리.
	if (file == nullptr)
	{
		std::cout << "맵 파일 열기 실패.\n";
		__debugbreak();
		return;
	}

	// 파일 읽기.
	// 끝위치로 이동.
	fseek(file, 0, SEEK_END);

	// 이동한 위치의 FP 가져오기.
	size_t readSize = ftell(file);

	// FP 원위치.
	rewind(file);

	// 파일 읽어서 버퍼에 담기.
	char* buffer = new char[readSize + 1];
	size_t bytesRead = fread(buffer, 1, readSize, file);

	if (readSize != bytesRead)
	{
		std::cout << "읽어온 크기가 다름\n";
		__debugbreak();
		return;
	}

	buffer[readSize] = '\0';

	// 파일 읽을 때 사용할 인덱스.
	int index = 0;

	// 좌표 계산을 위한 변수 선언.
	int xPosition = 0;
	int yPosition = 0;

	// 해석 (파싱-Parcing).
	while (index < (int)bytesRead)
	{
		// 한 문자씩 읽기.
		char mapChar = buffer[index++];

		// 개행 문자인 경우 처리.
		if (mapChar == '\n')
		{
			++yPosition;
			xPosition = 0;
			continue;
		}

		// 맵 문자가 1이면 Wall 액터 생성
		if (mapChar == '1')
		{
			Wall* wall = new Wall(Vector2(xPosition, yPosition));
			actors.PushBack(wall);
			map.PushBack(wall);
		}

		// 맵 문자가 0이면 그라운드 액터 생성
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

	AddActor(new Player("o", this));
	AddActor(new Enemy("x"));

	// 버퍼 삭제.
	delete[] buffer;

	fclose(file);
}

void GameLevel::Update(float deltaTime)
{
	Super::Update(deltaTime);

	// 예외 처리.
	if (deltaTime > 1.0f)
	{
		return;
	}

	// ESC 키로 종료.
	//if (Engine::Get().GetKeyDown(VK_ESCAPE))
	//{
	//	Game::Get().ToggleMenu();
	//}

	// Wall 또는 Ground가 아니면 IsInAir = true

	//SpawnEnemy(deltaTime);

	// 플레이어 탄약과 적의 충돌 처리.
	ProcessCollisionPlayerBulletAndEnemy();

	// 적과 플레이어의 충돌 처리.
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

		Sleep(2000);

		Engine::Get().QuitGame();
	}

	// 점수 출력.
	char buffer[256];
	snprintf(buffer, 256, "Score: %d", score);
	Engine::Get().Draw(Vector2(0, Engine::Get().ScreenSize().y - 1), buffer);
}

void GameLevel::ProcessCollisionPlayerBulletAndEnemy()
{
}

void GameLevel::ProcessCollisionPlayerAndEnemy()
{
	// 탄약 및 적 캐릭터 배열 선언.
	List<Enemy*> enemies;
	Player* player = nullptr;

	// 액터 목록을 순회하면서 탄약과 적 캐릭터를 찾아 배열에 추가.
	for (Actor* actor : actors)
	{
		// 플레이어가 설정되지 않았으면 플레이어로 형변환.
		if (!player)
		{
			player = actor->As<Player>();
			continue;
		}

		// 적으로 형변환 성공하면 목록에 추가.
		Enemy* enemy = actor->As<Enemy>();
		if (enemy)
		{
			enemies.PushBack(enemy);
		}
	}

	// 플레이어를 못찾았거나 적 탄약이 없으면 충돌 처리하지 않고 종료.
	if (player == nullptr || enemies.Size() == 0)
	{
		return;
	}

	// 두 배열을 순회하면서 충돌 처리.
	for (Enemy* enemy : enemies)
	{
		// 플레이어가 비활성화 상태이면 건너뛰기.
		if (!player->IsActive())
		{
			continue;
		}

		// 적과 탄약이 충돌했는지 확인.
		if (player->Intersect(*enemy))
		{
			isPlayerDead = true;
			playerDeadPosition = Vector2(player->Position().x + player->Width() / 2, player->Position().y);
			player->Destroy();
		}
	}
}

void GameLevel::SpawnEnemy(float deltaTime)
{
	AddActor(new Enemy("x"));
}

bool GameLevel::CheckGameClear()
{
	List<Enemy*> enemies;

	for (Actor* actor : actors)
	{
		// 적으로 형변환 성공하면 목록에 추가.
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
	// 게임이 클리어된 경우 바로 종료.
	if (isGameClear)
	{
		return false;
	}

	// 이동하려는 위치에 벽이 있는지 확인.
	DrawableActor* searchedActor = nullptr;

	// 먼저 이동하려는 위치의 액터 찾기.
	for (auto* actor : map)
	{
		if (actor->Position() == position)
		{
			searchedActor = actor;
			break;
		}
	}

	// 검색한 액터가 벽인지 확인.
	if (searchedActor->As<Wall>())
	{
		return false;
	}

	// 검색한 액터가 이동 가능한 액터(땅/타겟)인지 확인.
	if (searchedActor->As<Ground>())
	{
		return false;
	}

	return true;
}

bool GameLevel::IsOnGround(const Vector2& position)
{
	// 이동하려는 위치에 벽이 있는지 확인.
	Actor* searchedActor = nullptr;

	// 먼저 이동하려는 위치의 액터 찾기.
	for (auto* actor : actors)
	{
		if (actor->Position() == position)
		{
			searchedActor = actor;
			break;
		}
	}

	if (searchedActor->As<Ground>())
	{
		return true;
	}

	return false;
}