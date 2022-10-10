#include "stdafx.h"
#include "SceneManager.h"

SceneManager::SceneManager()
{
}

SceneManager::~SceneManager()
{
	DeleteDC(memDC);
	
	for (SITER iter = sceneMap.begin(); iter != sceneMap.end(); ++iter)
		delete iter->second;
	sceneMap.clear();
}

void SceneManager::add(int key, BaseScene * scene)
{
	sceneMap.insert(pair<int, BaseScene*>(key, scene));
}

void SceneManager::init(HWND hWnd)
{
	currState = SCENE::TITLE;
	backgroundColor = NULL;

	this->hWnd = hWnd;
	HDC hdc = GetDC(hWnd);

	GetClientRect(hWnd, &this->clirect);

	//// 전면버퍼에 상응하는 후면 버퍼를 생성한다.
	this->memDC = CreateCompatibleDC(hdc);

	//// 후면버퍼의 실질적인 메모리 공간을 생성한다.
	this->memBuffer = CreateCompatibleBitmap(hdc, clirect.right, clirect.bottom);

	//// 후면버퍼에 생성한 비트맵을 연결한다.
	SelectObject(this->memDC, this->memBuffer);

	ReleaseDC(hWnd, hdc);

	sceneMap[currState]->init();
}


void SceneManager::changeState(SCENE state, int stage)
{
	// 등록되어 있는 신이 아니라면 함수를 종료한다.
	if (sceneMap.find(state) == sceneMap.end())
		return;

	// 현재 신과 변경하려는 상태가 같다면 함수를 종료한다.
	if (currState == state)
		return;

	// 이전 신을 종료한다.
	sceneMap[currState]->Exit();

	// 현재 신에 관한 정보를 재설정한다.
	if(stage == 0)
		sceneMap[state]->Enter();
	else
		sceneMap[state]->Enter(stage);

	this->currState = state;
}

void SceneManager::input(float delta)
{
	sceneMap[currState]->input(delta);
}

void SceneManager::update(float delta)
{
	sceneMap[currState]->update(delta);
}

void SceneManager::render()
{
	HDC hdc = GetDC(this->hWnd);

	sceneMap[currState]->render(this->memDC, this->clirect);

	BitBlt(hdc, 0, 0, clirect.right, clirect.bottom, memDC, 0, 0, SRCCOPY);

	ReleaseDC(hWnd, hdc);
}

void SceneManager::run(float delta)
{
	this->update(delta);
	this->input(delta);
	this->render();
}