#pragma once
#include "stdafx.h"
#include "BaseScene.h"
#include "SceneManager.h"

class TitleScene : public BaseScene
{
private:
	HBITMAP titleImage;
	int stageNum;
	bool* playable;
	int selectStage;
	RECT stageRect;
public:
	TitleScene(HWND hWnd);
	virtual ~TitleScene();

	virtual void init();
	virtual void update(float delta);
	virtual void input(float delta);
	virtual void render(HDC hdc, RECT clirect);
	virtual void Enter();
	virtual void Enter(int clearStage);
	virtual void Exit();
};