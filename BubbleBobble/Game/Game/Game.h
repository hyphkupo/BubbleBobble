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

	// �޴��� - ����� ��ȯ �Լ�.
	void ToggleMenu();

	// �̱��� ���� �Լ�.
	static Game& Get()
	{
		//Lazy Singleton Pattern.	=> �̱��� ��ü�� �� �� ��ü �ʱ�ȭ
		//static Game* instance = new Game();
		//return *instance;		
		// �Լ� �ȿ��� �����ϴ� �����̾ �츮�� ���� ã�ư��� ������� �� ...

		return *instance;
	}

private:
	// �޴��� �����ְ� �ִ����� ��Ÿ���� ����.
	bool showMenu = false;

	// �� ����.
	Level* menuLevel = nullptr;
	Level* backLevel = nullptr;

	// �̱��� ���� ��ü.
	static Game* instance;
};