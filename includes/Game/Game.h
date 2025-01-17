#pragma once

#include "Engine/Engine.h"

class Game : public Engine
{
public:
	Game();
	~Game();

	// 메뉴씬 - 데모씬 전환 함수.
	void ToggleMenu();

	// 싱글톤 접근 함수.
	static Game& Get() { return *instance; }

private:
	// 메뉴를 보여주고 있는지를 나타내는 변수.
	bool showMenu = false;

	// 씬 변수.
	Level* menuLevel = nullptr;
	Level* backLevel = nullptr;

	// 싱글톤 구현 객체.
	static Game* instance;
};