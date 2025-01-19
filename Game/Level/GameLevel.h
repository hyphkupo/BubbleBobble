#pragma once

#include <Level/Level.h>
#include <Math/Vector2.h>

// ���ڹ� ���� ����.
class DrawableActor;
class Player;
class GameLevel : public Level
{
	RTTI_DECLARATIONS(GameLevel, Level)

public:
	GameLevel();

	// ������Ʈ �Լ�.
	virtual void Update(float deltaTime) override;
	virtual void Draw() override;

	// �÷��̾ �̵��� ������ �� Ȯ���ϴ� �Լ�.
	bool CanPlayerMove(const Vector2& position);

	bool IsOnGround(const Vector2& position);
	bool IsOnWall = true;
	bool IsInAir = false;

	List<int> GroundPosition;

	bool isPlayerDead = false;

private:
	// �÷��̾� ź��� ���� �浹 ó��.
	void ProcessCollisionPlayerBulletAndEnemy();

	// ���� �÷��̾��� �浹 ó��.
	void ProcessCollisionPlayerAndEnemy();

	// �� ���� �Լ�
	void SpawnEnemy(float deltaTime);

	// �ڽ��� �ű� �� ������ Ŭ�����ߴ��� Ȯ���ϴ� �Լ�.
	bool CheckGameClear();

private:
	// ����.
	int score = 0;

	// ��/�� ���� �迭.
	List<DrawableActor*> map;

	// �÷��̾� ����.
	Player* player = nullptr;

	// ���� Ŭ���� ����.
	bool isGameClear = false;

	Vector2 playerDeadPosition;
};