#include <iostream>
#include "Engine/engine.h"
#include "Level/GameLevel.h"
#include "Game/Game.h"

int main()
{
	// 메모리 누수 확인.
	CheckMemoryLeak();

	Game game;
	game.LoadLevel(new GameLevel);
	game.Run();
}