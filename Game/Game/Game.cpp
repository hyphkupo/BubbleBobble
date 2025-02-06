//#include "Game.h"
//
//Game::Game()
//{
//	// 커서 안보이게 설정.
//	SetCursorType(CursorType::NoCursor);
//}
//
//Game::~Game()
//{
//}

#include "Game.h"
#include "Level/MenuLevel.h"

Game* Game::instance = nullptr;

Game::Game()
{
	// 커서 안보이게 설정.
	SetCursorType(CursorType::NoCursor);

	// 싱글톤 객체 설정.
	instance = this;

	// 메뉴 레벨 생성.
	menuLevel = new MenuLevel();
}

Game::~Game()
{
	// 씬 삭제 처리.
	if (showMenu)
	{
		// Engine의 메인 레벨이 메뉴 레벨인 상태.
		delete backLevel;
		backLevel = nullptr;
		mainLevel = nullptr;
	}
	else
	{
		// Engine의 메인 레벨이 데모 레벨인 상태.
		delete mainLevel;
		mainLevel = nullptr;
	}
	
	// 메뉴 레벨 삭제.
	delete menuLevel;
	menuLevel = nullptr;
}

void Game::ToggleMenu()
{
	// 화면 지우기.
	system("cls");

	// 메뉴 플래그 값 뒤집기.
	showMenu = !showMenu;

	// 메뉴를 보이는 경우.
	if (showMenu)
	{
		// 현재의 메인 레벨을 뒤에 저장.
		backLevel = mainLevel;

		// 메인 레벨을 메뉴 레벨로 전환.
		mainLevel = menuLevel;
	}
	else
	{
		// 메뉴를 감추는 경우에는,
		// 뒤에 저장했던 데모 레벨을 다시 메인 레벨로 설정.
		mainLevel = backLevel;
	}
}