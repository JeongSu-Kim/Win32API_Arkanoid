#include "stdafx.h"
#include "BaseScene.h"

BaseScene::BaseScene(HWND hWnd)
{
	this->hWnd = hWnd;
	GetClientRect(hWnd, &clirect);
}

BaseScene::~BaseScene()
{
}

void BaseScene::init()
{
}

void BaseScene::update(float delta)
{
}

void BaseScene::input(float delta)
{
}

void BaseScene::render(HDC hdc, RECT clirect)
{
}

void BaseScene::Enter()
{
}

void BaseScene::Enter(int num)
{
}

void BaseScene::Exit()
{
}
