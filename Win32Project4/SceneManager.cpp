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

	//// ������ۿ� �����ϴ� �ĸ� ���۸� �����Ѵ�.
	this->memDC = CreateCompatibleDC(hdc);

	//// �ĸ������ �������� �޸� ������ �����Ѵ�.
	this->memBuffer = CreateCompatibleBitmap(hdc, clirect.right, clirect.bottom);

	//// �ĸ���ۿ� ������ ��Ʈ���� �����Ѵ�.
	SelectObject(this->memDC, this->memBuffer);

	ReleaseDC(hWnd, hdc);

	sceneMap[currState]->init();
}


void SceneManager::changeState(SCENE state, int stage)
{
	// ��ϵǾ� �ִ� ���� �ƴ϶�� �Լ��� �����Ѵ�.
	if (sceneMap.find(state) == sceneMap.end())
		return;

	// ���� �Ű� �����Ϸ��� ���°� ���ٸ� �Լ��� �����Ѵ�.
	if (currState == state)
		return;

	// ���� ���� �����Ѵ�.
	sceneMap[currState]->Exit();

	// ���� �ſ� ���� ������ �缳���Ѵ�.
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