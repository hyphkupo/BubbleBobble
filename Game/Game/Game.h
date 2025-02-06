//#pragma once
//
//#include "Engine/Engine.h"
//
//class Game : public Engine
//{
//public:
//	Game();
//	~Game();
//};

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
	static Game& Get()
	{
		//Lazy Singleton Pattern.	=> 싱글톤 객체를 쓸 때 객체 초기화
		//static Game* instance = new Game();
		//return *instance;		
		// 함수 안에서 생성하는 패턴이어서 우리가 따로 찾아가서 지워줘야 함 ...

		return *instance;
	};

private:
	// 메뉴를 보여주고 있는지를 나타내는 변수.
	bool showMenu = false;

	// 씬 변수.
	Level* menuLevel = nullptr;
	//Level* mainLevel = nullptr;
	Level* backLevel = nullptr;

	// 싱글톤 구현 객체.
	static Game* instance;
};