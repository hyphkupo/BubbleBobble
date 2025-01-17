#include "GameLevel.h"
#include "GameLevel.h"
#include "GameLevel.h"
#include "Engine/Engine.h"
#include "Actor/Player.h"
#include "Actor/Wall.h"
#include "Actor/Ground.h"

#include "Actor/Enemy.h"

#include <Windows.h>

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

		// 맵 문자가 1이면 Wall 액터 생성.
		if (mapChar == '1')
		{
			Wall* wall = new Wall(Vector2(xPosition, yPosition));
			actors.PushBack(wall);
			map.PushBack(wall);
		}

		// 맵 문자가 .이면 그라운드 액터 생성.
		else if (mapChar == '0')
		{
			Ground* ground = new Ground(Vector2(xPosition, yPosition));
			actors.PushBack(ground);
			map.PushBack(ground);
		}

		++xPosition;
	}

	AddActor(new Player("o", this));

	// 버퍼 삭제.
	delete[] buffer;

	fclose(file);
}

GameLevel::~GameLevel()
{
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
	if (Engine::Get().GetKeyDown(VK_ESCAPE))
	{
		Engine::Get().QuitGame();
	}

	AddActor(new Enemy("x"));

}

bool GameLevel::CanPlayerMove(const Vector2& position)
{
	return false;
}



bool GameLevel::CheckGameClear()
{
	return false;
}