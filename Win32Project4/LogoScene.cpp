#include "stdafx.h"
#include "LogoScene.h"

LogoScene::LogoScene(HWND hWnd) : BaseScene(hWnd)
{
}

LogoScene::~LogoScene()
{
}

void LogoScene::init()
{
	this->backgroundColor = CreateSolidBrush(RGB(255, 255, 255));
	this->startTime = GetTickCount();
	this->logoImage = (HBITMAP)LoadImage(NULL, TEXT("IMAGE/LOGO.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);
}

void LogoScene::update(float delta)
{
	DWORD overTime = GetTickCount() - this->startTime;
	if(overTime > 2000)
		SCENEMNG->changeState(SceneManager::TITLE, 0);
}

void LogoScene::input(float delta)
{
}

void LogoScene::render(HDC hdc, RECT clirect)
{
	FillRect(hdc, &clirect, this->backgroundColor);
	HDC logohdc = CreateCompatibleDC(hdc);
	HBITMAP oldBitmap = (HBITMAP)SelectObject(logohdc, this->logoImage);
	BitBlt(hdc, 0, 200, 498, 106, logohdc, 0, 0, SRCCOPY);
	//SelectObject(logohdc, oldBitmap);
	DeleteDC(logohdc);
}

void LogoScene::Enter()
{
}

void LogoScene::Exit()
{
	DeleteObject(this->backgroundColor);
	DeleteObject(this->logoImage);
	this->backgroundColor = NULL;
	this->logoImage = NULL;
}
