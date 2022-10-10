#pragma once
#include "stdafx.h"
#include "TSingleton.h"
#include "BaseScene.h"

class SceneManager : public TSingleton<SceneManager>
{
private:
	friend TSingleton<SceneManager>;

	typedef map<int, BaseScene *> SCENEMAP;
	typedef SCENEMAP::iterator SITER;

public:
	typedef enum SCENE
	{
		LOGO,
		TITLE,
		GAME,
	};

private:
	SCENEMAP sceneMap;
	SCENE currState;

	RECT clirect;

	HWND hWnd;
	// 후면 버퍼를 생성하기 위한 메모리 dc
	HDC memDC;
	// 후면 버퍼의 실질적인 메모리 공간을 나타내는 비트맵
	HBITMAP memBuffer;
	// 후면 버퍼의 배경색을 그리기 위한 브러쉬
	HBRUSH backgroundColor;

private:
	SceneManager();

public:
	virtual ~SceneManager();

	// 개별 신 등록 함수.
	void add(int key, BaseScene * scene);
	// 초기화 함수.
	void init(HWND hWnd);
	// 신 상태 변경
	void changeState(SCENE state, int stage);

public:
	void input(float delta);
	void update(float delta);
	void render();

	void run(float delta);
};

#define SCENEMNG SceneManager::GetInstance()