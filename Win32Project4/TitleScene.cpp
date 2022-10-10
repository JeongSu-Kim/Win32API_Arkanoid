#include "stdafx.h"
#include "TitleScene.h"

TitleScene::TitleScene(HWND hWnd) : BaseScene(hWnd)
{
}

TitleScene::~TitleScene()
{
}

void TitleScene::init()
{
	this->backgroundColor = CreateSolidBrush(RGB(255, 255, 255));
	this->titleImage = (HBITMAP)LoadImage(NULL, TEXT("IMAGE/MYTITLE.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);
	
	this->stageNum = 4;
	this->playable = new bool[stageNum];
	this->playable[0] = true;
	for (int i = 1; i < stageNum; i++)
	{
		this->playable[i] = false;
	}
	this->selectStage = 0;

	stageRect.left = clirect.right / 2 - 50;
	stageRect.right = clirect.right / 2 + 50;
	stageRect.top = clirect.bottom / 2;
	stageRect.bottom = clirect.bottom / 2 + 30;
}

void TitleScene::update(float delta)
{
}

void TitleScene::input(float delta)
{
	if (GetAsyncKeyState(VK_LBUTTON) & 0x8000)
	{
		POINT mousePos;
		GetCursorPos(&mousePos);
		ScreenToClient(this->hWnd, &mousePos);
		if (mousePos.x >= stageRect.left && mousePos.x <= stageRect.right)
		{
			if (mousePos.y >= clirect.bottom / 2 && mousePos.y < clirect.bottom / 2 + 30)
				selectStage = 1;
			else if (mousePos.y >= clirect.bottom / 2 + 30 && mousePos.y < clirect.bottom / 2 + 60)
				selectStage = 2;
			else if (mousePos.y >= clirect.bottom / 2 + 60 && mousePos.y < clirect.bottom / 2 + 90)
				selectStage = 3;
			else if (mousePos.y >= clirect.bottom / 2 + 90 && mousePos.y < clirect.bottom / 2 + 120)
				selectStage = 4;

			SCENEMNG->changeState(SceneManager::GAME, selectStage);
		}
	}
}

void TitleScene::render(HDC hdc, RECT clirect)
{
	FillRect(hdc, &clirect, this->backgroundColor);
	HDC logohdc = CreateCompatibleDC(hdc);
	HBITMAP oldBitmap = (HBITMAP)SelectObject(logohdc, this->titleImage);
	BitBlt(hdc, 0, 0, clirect.right, clirect.bottom, logohdc, 0, 0, SRCCOPY);
	//SelectObject(logohdc, oldBitmap);
	DeleteDC(logohdc);


	
	SetBkColor(hdc, RGB(200, 200, 200));
	stageRect.top = clirect.bottom / 2 ;
	stageRect.bottom = clirect.bottom / 2 + 30;
	SetTextColor(hdc, RGB(10, 10, 10));
	//Rectangle(hdc, stageRect.left, stageRect.top, stageRect.right, stageRect.bottom);
	DrawText(hdc, _T("stage 1"), -1, &stageRect, DT_CENTER | DT_VCENTER);
	
	stageRect.top = clirect.bottom / 2 + 30;
	stageRect.bottom = clirect.bottom / 2 + 60;
	SetTextColor(hdc, RGB(10, 10, 10));
	DrawText(hdc, _T("stage 2"), -1, &stageRect, DT_CENTER | DT_VCENTER);

	stageRect.top = clirect.bottom / 2 + 60;
	stageRect.bottom = clirect.bottom / 2 + 90;
	SetTextColor(hdc, RGB(10, 10, 10));
	DrawText(hdc, _T("stage 3"), -1, &stageRect, DT_CENTER | DT_VCENTER);

	stageRect.top = clirect.bottom / 2 + 90;
	stageRect.bottom = clirect.bottom / 2 + 120;
	SetTextColor(hdc, RGB(10, 10, 10));
	DrawText(hdc, _T("stage 4"), -1, &stageRect, DT_CENTER | DT_VCENTER);
}

void TitleScene::Enter()
{
	this->init();
}

void TitleScene::Enter(int clearStage)
{
	this->init();
	playable[clearStage] = true;
}

void TitleScene::Exit()
{
	DeleteObject(backgroundColor);
}