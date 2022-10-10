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
	// �ĸ� ���۸� �����ϱ� ���� �޸� dc
	HDC memDC;
	// �ĸ� ������ �������� �޸� ������ ��Ÿ���� ��Ʈ��
	HBITMAP memBuffer;
	// �ĸ� ������ ������ �׸��� ���� �귯��
	HBRUSH backgroundColor;

private:
	SceneManager();

public:
	virtual ~SceneManager();

	// ���� �� ��� �Լ�.
	void add(int key, BaseScene * scene);
	// �ʱ�ȭ �Լ�.
	void init(HWND hWnd);
	// �� ���� ����
	void changeState(SCENE state, int stage);

public:
	void input(float delta);
	void update(float delta);
	void render();

	void run(float delta);
};

#define SCENEMNG SceneManager::GetInstance()