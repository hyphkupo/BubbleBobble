#pragma once

#include <Level/Level.h>
#include <Math/Vector2.h>

class DrawableActor;
class Player;
class GameLevel : public Level
{
	RTTI_DECLARATIONS(GameLevel, Level)

public:
	GameLevel();

	// 업데이트 함수.
	virtual void Update(float deltaTime) override;
	virtual void Draw() override;

	// 플레이어가 이동이 가능한 지 확인하는 함수.
	bool CanPlayerMove(const Vector2& position);

	bool IsOnGround(const Vector2& position);
	bool IsOnWall = true;
	bool IsInAir = false;

	//List<int> GroundPosition;

	bool isPlayerDead = false;

	// 플레이어의 버블 발사 방향 결정 변수
	int flag = 0;

	// 움직이는 버블 방향 고정용 변수
	List<bool> BubbleDirection;

private:
	// 플레이어 버블과 적의 충돌 처리.
	void ProcessCollisionPlayerBubbleAndEnemy();

	// 적과 플레이어의 충돌 처리.
	void ProcessCollisionPlayerAndEnemy();

	// 적 생성 함수
	void SpawnEnemy(float deltaTime);

	// 박스를 옮긴 뒤 게임을 클리어했는지 확인하는 함수.
	bool CheckGameClear();

private:
	// enemy 위치 업데이트용 변수
	int xPosition = 0;
	int yPosition = 0;

	// 점수.
	int score = 0;

	// 벽/땅 액터 배열.
	List<DrawableActor*> map;

	// 플레이어 액터.
	Player* player = nullptr;

	// 게임 클리어 변수.
	bool isGameClear = false;

	Vector2 playerDeadPosition;
};