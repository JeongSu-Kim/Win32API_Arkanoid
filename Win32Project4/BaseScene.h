#pragma once
#include "stdafx.h"

class BaseScene
{
protected:
	HWND hWnd;
	RECT clirect;
	HBRUSH backgroundColor;
public:
	BaseScene(HWND hWnd);
	virtual ~BaseScene();

	virtual void init();
	virtual void update(float delta);
	virtual void input(float delta);
	virtual void render(HDC hdc, RECT clirect);
	virtual void Enter();
	virtual void Enter(int num);
	virtual void Exit();

};
