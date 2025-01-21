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

	//bool IsOnGround(const Vector2& position);
	//bool IsOnWall = true;
	//bool IsInAir = false;

	//List<int> GroundPosition;

	bool isPlayerDead = false;

private:
	// 플레이어 버블과 적의 충돌 처리.
	void ProcessCollisionPlayerBubbleAndEnemy();

	// 적과 플레이어의 충돌 처리.
	void ProcessCollisionPlayerAndEnemy();

	// 적 생성 함수
	//void SpawnEnemy(float deltaTime);

	// 게임을 클리어했는지 확인하는 함수
	bool CheckGameClear();

private:
	// 점수
	int score = 0;

	// 벽/땅 액터 배열
	List<DrawableActor*> map;

	// 플레이어 액터
	Player* player = nullptr;

	// 게임 클리어 변수
	bool isGameClear = false;

	//Vector2 playerDeadPosition;
};