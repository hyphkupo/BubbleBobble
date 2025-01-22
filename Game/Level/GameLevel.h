#pragma once

#include <Level/Level.h>
#include <Math/Vector2.h>

class DrawableActor;
class Player;
class Enemy;
class GameLevel : public Level
{
	RTTI_DECLARATIONS(GameLevel, Level)

public:
	GameLevel();

	virtual void Update(float deltaTime) override;
	virtual void Draw() override;

	bool isGround(const Vector2& position);

	// �÷��̾ �̵��� ������ �� Ȯ���ϴ� �Լ�
	bool CanPlayerMove(const Vector2& position);

	bool isPlayerDead = false;

	int stageNumber = 3;

private:
	// �������� ���� �ε� �Լ�
	void LoadNextStage();

	// �÷��̾� ����� ���� �浹 ó��
	void ProcessCollisionPlayerBubbleAndEnemy();

	// ���� �÷��̾��� �浹 ó��
	void ProcessCollisionPlayerAndEnemy();

	// ������ Ŭ�����ߴ��� Ȯ���ϴ� �Լ�
	bool CheckGameClear();

private:
	// ��/�� ���� �迭
	List<DrawableActor*> map;

	// ����
	int score = 0;

	// �÷��̾� ����
	Player* player = nullptr;

	// ���� Ŭ���� ����
	bool isGameClear = false;
	int gameClearNumber = 0;

	Player* p = nullptr;
	Enemy* e1 = nullptr;
	Enemy* e2 = nullptr;
};