#pragma once
#include "stdafx.h"
#include "BaseScene.h"
#include "Block.h"
#include "MapEditor.h"
#include "SceneManager.h"

class GameScene : public BaseScene
{
private:
	map<int, Block*> blockList;
	typedef map<int, Block*>::iterator bIter;

	int collisionCheckKey;
	int bardir;

	Ball* pball;
	PlayerBar* pbar;

	int bCount;
	int lifeCount;

	int toTitle;
	int currStage;

public:
	GameScene(HWND hWnd);
	virtual ~GameScene();

	virtual void init();
	virtual void update(float delta);
	virtual void input(float delta);
	virtual void render(HDC hdc, RECT clirect);
	virtual void Enter();
	virtual void Enter(int stage);
	virtual void Exit();

	Block* collisionBlock();
	void colision(Block* colBlock);
	void roadStage(int stage);
	void gameClear();
	void gameOver();
};