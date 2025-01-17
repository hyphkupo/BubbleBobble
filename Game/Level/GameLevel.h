#pragma once

#include <Level/Level.h>
#include <Math/Vector2.h>

// ���ڹ� ���� ����.
class DrawableActor;
class Player;
class Box;
class Target;
class GameLevel : public Level
{
	RTTI_DECLARATIONS(GameLevel, Level)

public:
	GameLevel();

	// ������Ʈ �Լ�.
	virtual void Update(float deltaTime) override;


	// �÷��̾ �̵��� ������ �� Ȯ���ϴ� �Լ�.
	bool CanPlayerMove(const Vector2& position);

	bool IsOnGround = false;
	bool IsOnWall = true;
	bool IsInAir = false;

private:
	// �ڽ��� �ű� �� ������ Ŭ�����ߴ��� Ȯ���ϴ� �Լ�.
	bool CheckGameClear();

private:
	// ��/�� ���� �迭.
	List<DrawableActor*> map;

	// �ڽ� ����.
	List<Box*> boxes;

	// Ÿ�� ����.
	List<Target*> targets;

	// �÷��̾� ����.
	Player* player = nullptr;

	// ���� Ŭ���� ����.
	bool isGameClear = false;
};