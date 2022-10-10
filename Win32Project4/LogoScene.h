#pragma once
#include "stdafx.h"
#include "BaseScene.h"
#include "SceneManager.h"

class LogoScene : public BaseScene
{
private:
	DWORD startTime;
	HBITMAP logoImage;

public:
	LogoScene(HWND hWnd);
	virtual ~LogoScene();

	virtual void init();
	virtual void update(float delta);
	virtual void input(float delta);
	virtual void render(HDC hdc, RECT clirect);
	virtual void Enter();
	virtual void Exit();
};