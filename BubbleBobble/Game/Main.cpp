#include <iostream>
#include "Engine/engine.h"
#include "Level/GameLevel.h"
#include "Game/Game.h"

int main()
{
	// �޸� ���� Ȯ��.
	CheckMemoryLeak();

	Game game;
	game.LoadLevel(new GameLevel);
	
	game.Run();
}