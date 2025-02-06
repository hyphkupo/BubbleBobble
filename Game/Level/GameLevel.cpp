#include "GameLevel.h"
#include "Engine/Engine.h"
#include "Level/Level.h"

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
	LoadNextStage();
}

void GameLevel::Update(float deltaTime)
{
	Super::Update(deltaTime);

	// 예외 처리.
	if (deltaTime > 1.0f)
	{
		return;
	}

	// 플레이어 버블과 적의 충돌 처리.
	ProcessCollisionPlayerBubbleAndEnemy();

	// 적과 플레이어의 충돌 처리.
	ProcessCollisionPlayerAndEnemy();

	char resultBuffer[1024];

	if (isPlayerDead)
	{
		//Engine::Get().Draw(Vector2(Engine::Get().ScreenSize().x - 10, Engine::Get().ScreenSize().y - 1), "Game Over!");
		Engine::Get().SetCursorPosition(Vector2(Engine::Get().ScreenSize().x - 10, Engine::Get().ScreenSize().y - 1));
		Log("Game Over!");
		//Engine::Get().Present();

		Sleep(3000);

		Engine::Get().QuitGame();
	}

	else if (CheckGameClear())
	{
		//Engine::Get().Draw(Vector2(Engine::Get().ScreenSize().x - 11, Engine::Get().ScreenSize().y - 1), "Game Clear!");
		Engine::Get().SetCursorPosition(Vector2(Engine::Get().ScreenSize().x - 11, Engine::Get().ScreenSize().y - 1));
		Log("Game Clear!");
		//Engine::Get().Present();

		Sleep(3000);

		++gameClearNumber;
		if (gameClearNumber == 3)
		{
			Engine::Get().QuitGame();
			return;
		}

		// map 데이터 삭제
		for (int ix = 0; ix < map.Size();)
		{
			map.Erase(ix);
		}

		if (stageNumber == 3)
		{
			p->Destroy();
			e1->Destroy();
		}

		else
		{
			p->Destroy();
			e1->Destroy();
			e2->Destroy();
		}

		LoadNextStage();
	}
}

void GameLevel::Draw()
{
	Super::Draw();

	// 점수 출력.
	char buffer[256];
	snprintf(buffer, 256, "Score: %d", score);
	Engine::Get().Draw(Vector2(0, Engine::Get().ScreenSize().y - 1), buffer);
}

bool GameLevel::isGround(const Vector2& position)
{
	// 이동하려는 위치에 땅이 있는지 확인
	DrawableActor* searchedActor = nullptr;

	// 이동하려는 위치의 액터 찾기
	for (auto* actor : map)
	{
		if (actor->Position() == position)
		{
			searchedActor = actor;
			break;
		}
	}

	// 검색한 액터가 땅 액터인지 확인
	if (searchedActor->As<Ground>())
	{
		return true;
	}

	return false;
}

void GameLevel::LoadNextStage()
{
	// 커서 감추기.
	Engine::Get().SetCursorType(CursorType::NoCursor);

	// 맵 파일 불러와 레벨 로드.
	// 파일 읽기.
	FILE* file = nullptr;

	char stageFileNameBuffer[256] = "../Assets/Maps/Stage";
	char stageCharNumber[256];
	_itoa_s(stageNumber, stageCharNumber, 10);
	strcat_s(stageFileNameBuffer, 256, stageCharNumber);
	strcat_s(stageFileNameBuffer, 256, ".txt");

	//fopen_s(&file, "../Assets/Maps/Stage1.txt", "rb");
	fopen_s(&file, stageFileNameBuffer, "rb");

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

	if (stageNumber == 1)
	{
		p = new Player("p", this);
		e1 = new Enemy("x", 9, 22, 4, this);
		e2 = new Enemy("x", 9, 22, 7, this);

		AddActor(p);
		AddActor(e1);
		AddActor(e2);
	}
	
	else if (stageNumber == 2)
	{
		p = new Player("p", this);
		e1 = new Enemy("x", 10, 14, 3, this);
		e2 = new Enemy("x", 17, 21, 3, this);

		AddActor(p);
		AddActor(e1);
		AddActor(e2);
	}

	else if (stageNumber == 3)
	{
		p = new Player("p", this);
		e1 = new Enemy("b", 1, 9, 16, this);

		AddActor(p);
		AddActor(e1);
	}

	delete[] buffer;

	fclose(file);

	++stageNumber;
}

// 플레이어의 버블과 적 충돌 처리
void GameLevel::ProcessCollisionPlayerBubbleAndEnemy()
{
	// 버블 및 적 캐릭터 배열 선언
	List<PlayerBubble*> bubbles;
	List<Enemy*> enemies;
	Player* player = nullptr;

	// 레벨에 배치된 액터를 순회하면서 리스트 채우기
	for (Actor* actor : actors)
	{
		// 플레이어가 설정되지 않았으면 플레이어로 형변환
		if (!player)
		{
			player = actor->As<Player>();
			continue;
		}

		// 형변환 후 확인해서 리스트 채우기
		PlayerBubble* bubble = actor->As<PlayerBubble>();
		if (bubble)
		{
			bubbles.PushBack(bubble);
			continue;
		}

		// 적으로 형변환 후 확인해서 리스트 채우기
		Enemy* enemy = actor->As<Enemy>();
		if (enemy)
		{
			enemies.PushBack(enemy);
		}
	}

	// 예외 처리
	if (bubbles.Size() == 0 || enemies.Size() == 0)
	{
		return;
	}

	// 두 배열을 순회하면서 충돌 처리
	for (PlayerBubble* bubble : bubbles)
	{
		for (Enemy* enemy : enemies)
		{
			// 적이 비활성화 상태라면 건너뛰기
			if (!enemy->IsActive())
			{
				continue;
			}

			// 충돌 처리
			if (enemy->Intersect(*bubble))
			{
				enemy->inBubble = true;

				if (enemy->inBubble)
				{
					if (stageNumber == 4)
					{
						enemy->RedrawImage("&", Color::Yellow);
					}

					else
					{
						enemy->RedrawImage("@", Color::Yellow);
					}
				}

				// 맵 범위를 벗어나면 적 제거
				if (enemy->Position().y < 1)
				{
					enemy->Destroy();
				}

				// 버블 제거
				bubble->Destroy();
			}
		}
	}
}

// 플레이어와 적 충돌 처리
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

		// 플레이어와 적이 충돌했는지 확인
		if (player->Intersect(*enemy) && !enemy->inBubble)
		{
			isPlayerDead = true;
			//playerDeadPosition = Vector2(player->Position().x + player->Width() / 2, player->Position().y);
			player->Destroy();
		}

		// 적이 플레이어에게 버블을 맞은 후 플레이어와 부딪혔다면 점수 추가, 적 제거
		if (player->Intersect(*enemy) && enemy->inBubble)
		{
			if (stageNumber == 4)
			{
				score += 300;
			}

			else
			{
				score += 100;
			}

			enemy->Destroy();
		}
	}
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