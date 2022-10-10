#include "stdafx.h"
#include "GameScene.h"

#define BALLSPEED_FORTEST 400
//130
#define BALLPOSX_FORTEST 0
//450
#define BARSIZE_FORTEST 120

GameScene::GameScene(HWND hWnd) : BaseScene(hWnd)
{
}

GameScene::~GameScene()
{
	this->Exit();
}

void GameScene::init()
{
	/*HDC hdc = GetDC(this->hWnd);

	//GetClientRect(hWnd, &clirect);

	//// 전면버퍼에 상응하는 후면 버퍼를 생성한다.
	this->memDC = CreateCompatibleDC(hdc);

	//// 후면버퍼의 실질적인 메모리 공간을 생성한다.
	this->memBuffer = CreateCompatibleBitmap(hdc, clirect.right, clirect.bottom);

	//// 후면버퍼에 생성한 비트맵을 연결한다.
	SelectObject(this->memDC, this->memBuffer);
	
	ReleaseDC(this->hWnd, hdc); */

	this->backgroundColor = CreateSolidBrush(RGB(230, 230, 230));

	pball = new Ball;
	pball->setPen(BS_SOLID, 2, RGB(70, 180, 210));
	pball->setBrush(RGB(140, 220, 240));
	pball->setSize(20, 20);
	pball->setPosition((clirect.left + clirect.right) / 2 + BALLPOSX_FORTEST, clirect.bottom - 50 - pball->getRadius());
	pball->setLife(-1);
	pball->setSpeed(BALLSPEED_FORTEST);
	pball->setPower(1);
	pball->setDirection(Vector3(-0.5, -1, 0).normal());
	blockList.insert(pair<int, Block*>(0, pball));

	pbar = new PlayerBar;
	pbar->setPen(BS_SOLID, 3, RGB(180, 200, 60));
	pbar->setBrush(RGB(200, 220, 90));
	//pbar->setBrush(rainbow());
	pbar->setPosition((clirect.left + clirect.right) / 2, clirect.bottom - 40);
	pbar->setSize(BARSIZE_FORTEST, 20);
	pbar->setLife(-1);
	pbar->setSpeed(800);
	blockList.insert(pair<int, Block*>(1, pbar));

	//blockList.insert(pair<int, Block*>(2, createBlock(clirect.left + 10, (clirect.top + clirect.bottom) / 2, 20, clirect.bottom, -1, RGB(120, 120, 120))));
	//blockList.insert(pair<int, Block*>(3, createBlock(clirect.right - 10, (clirect.top + clirect.bottom) / 2, 20, clirect.bottom, -1, RGB(120, 120, 120))));
	//blockList.insert(pair<int, Block*>(4, createBlock((clirect.left + clirect.right) / 2, clirect.top + 10, clirect.right - 40, 20, -1, RGB(120, 120, 120))));
	blockList.insert(pair<int, Block*>(2, new Block(clirect.left + 10, (clirect.top + clirect.bottom) / 2, 20, clirect.bottom, -1, RGB(120, 120, 120))));
	blockList.insert(pair<int, Block*>(3, new Block(clirect.right - 10, (clirect.top + clirect.bottom) / 2, 20, clirect.bottom, -1, RGB(120, 120, 120))));
	blockList.insert(pair<int, Block*>(4, new Block((clirect.left + clirect.right) / 2, clirect.top + 10, clirect.right - 40, 20, -1, RGB(120, 120, 120))));

	collisionCheckKey = 0;

	this->hWnd = hWnd;
	this->lifeCount = 3;

	this->toTitle = -1;
}

void GameScene::update(float delta)
{
	if (!pball->isAttached())
	{
		//pball->move(pball->getDirection(), fps.getOneFrameTime() * pball->getSpeed());
		pball->move(pball->getDirection(), delta * pball->getSpeed());
		//collisionRect();
		Block* colBlock = collisionBlock();
		if (colBlock != nullptr)
			colision(colBlock);

		if (this->bCount == 0)
			gameClear();
	}

	if (pball->getPosition().y > clirect.bottom)
	{
		pball->setPosition(pbar->getPosition().x - 10, pbar->getPosition().y - 10 - pball->getRadius());
		pball->attach();
		pball->setDirection(Vector3(-0.5, -1, 0).normal());
		collisionCheckKey = 0;

		this->lifeCount -= 1;
		if (this->lifeCount == 0)
			gameOver();
	}
	//pball->setBrush(rainbow());
}

void GameScene::render(HDC hdc, RECT rect)
{
	FillRect(hdc, &rect, backgroundColor);

	for (bIter iter = blockList.begin(); iter != blockList.end(); ++iter)
	{
		if (iter->second->getLife() != 0)
			iter->second->draw(hdc);
	}

	if (this->toTitle != -1)
	{
		/*HDC ghdc = CreateCompatibleDC(hdc);
		HBRUSH bkc = CreateSolidBrush(RGB(255, 0, 0));
		FillRect(ghdc, &clirect, bkc);
		BitBlt(hdc, 0, 0, rect.right, rect.bottom, ghdc, 0, 0, SRCAND);
		DeleteDC(ghdc);*/
		RECT textRect;
		textRect.left = clirect.right / 2 - 100;
		textRect.right = clirect.right / 2 + 100;
		textRect.top = clirect.bottom / 2 - 100;
		textRect.bottom = clirect.bottom / 2 + 100;
		SetTextColor(hdc, RGB(10, 10, 10));
		if(this->toTitle == 0)
			DrawText(hdc, _T("Fale"), -1, &textRect, DT_CENTER | DT_VCENTER);
		else
			DrawText(hdc, _T("!Clear!"), -1, &textRect, DT_CENTER | DT_VCENTER);

	}
	
}

void GameScene::Enter()
{
	this->init();

	this->currStage = 1;
	this->roadStage(1);
}

void GameScene::Enter(int stage)
{
	this->init();
	
	this->currStage = stage;
	this->roadStage(stage);
}

void GameScene::Exit()
{
	for (bIter iter = blockList.begin(); iter != blockList.end(); ++iter)
	{
		delete(iter->second);
	}

	blockList.clear();

	//DeleteDC(memDC);
}

void GameScene::input(float delta)
{
	//float moveDistance = fps.getOneFrameTime() * pbar->getSpeed();
	float moveDistance = delta * pbar->getSpeed();
	RECT r = pbar->getRect();

	bardir = 0;

	if (GetAsyncKeyState(VK_LEFT) & 0x8000)
	{
		r.left -= moveDistance;
		r.right -= moveDistance;

		if (!IntersectRect(&r, &r, &blockList.find(2)->second->getRect()))
		{
			pbar->moveLeft(moveDistance);
			if (pball->isAttached())
				pball->move(Vector3(-1, 0, 0), moveDistance);
		}
		//else
		//{
		//	//IntersectRect(&r, &r, &blockList.find(2)->second->getRect());
		//	pbar->moveRight(r.right - r.left);
		//	if (pball->isAttached())
		//		pball->move(Vector3(1, 0, 0), r.right - r.left);
		//} 선체크 방식이라 스피드가 빠르면 사이 간격이 생기는 문제가 발생. 추후 해결

		bardir = -1;
	}

	if (GetAsyncKeyState(VK_RIGHT) & 0x8000)
	{
		r.left += moveDistance;
		r.right += moveDistance;

		if (!IntersectRect(&r, &r, &blockList.find(3)->second->getRect()))
		{
			pbar->moveRight(moveDistance);
			if (pball->isAttached())
				pball->move(Vector3(1, 0, 0), moveDistance);
		}

		bardir = 1;
	}

	if (GetAsyncKeyState(VK_SPACE) & 0x8000)
	{
		if (pball->isAttached())
			pball->detach();
		/*else
		{
			for (bIter iter = std::next(blockList.begin(), 1); iter != blockList.end(); ++iter)
			{
				if (iter->second->getLife() == 0)
				{
					iter->second->setLife(1);
				}
			}
		}*/
		if(this->toTitle != -1)
			SCENEMNG->changeState(SceneManager::TITLE, 0);
	}

	/*if (GetAsyncKeyState(VK_LBUTTON) & 0x8000 && this->toTitle != -1)
	{
		SCENEMNG->changeState(SceneManager::TITLE, 0);
	}*/
}

Block* GameScene::collisionBlock()
{
	float distance = 0;
	RECT colRect;
	Block* colBlock = nullptr;

	for (bIter iter = std::next(blockList.begin(), 1); iter != blockList.end(); ++iter)
	{
		if (iter->second->getLife() != 0)
		{
			if (iter->first != collisionCheckKey)
			{
				if (IntersectRect(&colRect, &pball->getRect(), &iter->second->getRect()))
				{
					//여기에 넣어보자
					//colBlock = iter->second;
					bool inTB = pball->getPosition().y > iter->second->getRect().top && pball->getPosition().y < iter->second->getRect().bottom;
					bool inLR = pball->getPosition().x > iter->second->getRect().left && pball->getPosition().x < iter->second->getRect().right;
					bool isR = inTB && pball->getPosition().x > iter->second->getRect().right;
					bool isL = inTB && pball->getPosition().x < iter->second->getRect().left;
					bool isT = inLR && pball->getPosition().y < iter->second->getRect().top;
					bool isB = inLR && pball->getPosition().y > iter->second->getRect().bottom;

					if (inTB && inLR)
					{
						int x = 0, y = 0;
						float moving_point;

						if (pball->getDirection().x > 0 && pball->getDirection().y > 0) //오른 아래
							x = iter->second->getRect().left;
						else if (pball->getDirection().x > 0 && pball->getDirection().y < 0) // 오른 위
							x = iter->second->getRect().left;
						else if (pball->getDirection().x < 0 && pball->getDirection().y < 0) // 왼 위
							x = iter->second->getRect().right;
						else if (pball->getDirection().x < 0 && pball->getDirection().y > 0) // 왼 아래
							x = iter->second->getRect().right;

						y = (pball->getDirection().y / pball->getDirection().x) * (x - pball->getPosition().x) + pball->getPosition().y;

						if (y >= iter->second->getRect().top && y <= iter->second->getRect().bottom)
						{
							if (pball->getDirection().x > 0)
								moving_point = iter->second->getRect().left - pball->getRadius();
							else
								moving_point = iter->second->getRect().right + pball->getRadius();

							pball->setPosition_y(pball->getPosition().y + (pball->getDirection().y / pball->getDirection().x) * (moving_point - pball->getPosition().x));
							pball->setPosition_x(moving_point);
						}
						else
						{
							if (pball->getDirection().y > 0)
								moving_point = iter->second->getRect().top - pball->getRadius();
							else
								moving_point = iter->second->getRect().bottom + pball->getRadius();

							pball->setPosition_x(pball->getPosition().x + (pball->getDirection().x / pball->getDirection().y) * (moving_point - pball->getPosition().y));
							pball->setPosition_y(moving_point);
						}
					}

					Vector3 disVec = iter->second->getPosition() - pball->getPosition();
					if (distance == 0 || distance > disVec.lenth())
					{
						distance = disVec.lenth();
						colBlock = iter->second;
						collisionCheckKey = iter->first; //이중충돌 방지
					}
				}
			}
		}
	}
	return colBlock;
}

void GameScene::colision(Block* colBlock)
{
	Vector3 normalVec;
	RECT cr = colBlock->getRect();
	Vector3 bp = pball->getPosition();
	float bpx = bp.x;
	float linetoRB = (float)((cr.bottom - cr.top) / (float)(cr.right - cr.left)) * (bp.x - cr.left) + cr.top;
	float linetoRT = (float)((cr.top - cr.bottom) / (float)(cr.right - cr.left)) * (bp.x - cr.left) + cr.bottom;

	if ((bp.y >= linetoRB) && (bp.y < linetoRT)) // L
	{
		if (pball->getDirection().x > 0)
			normalVec = Vector3(1, 0, 0);
		else
			normalVec = Vector3(0, 1, 0);
	}
	else if ((bp.y < linetoRB) && (bp.y >= linetoRT)) // R
	{
		if (pball->getDirection().x > 0)
			normalVec = Vector3(0, 1, 0);
		else
			normalVec = Vector3(1, 0, 0);
	}
	else if ((bp.y < linetoRB) && (bp.y < linetoRT)) // T
	{
		if (pball->getDirection().y > 0)
			normalVec = Vector3(0, 1, 0);
		else
			normalVec = Vector3(1, 0, 0);
	}
	else if ((bp.y >= linetoRB) && (bp.y >= linetoRT)) // B
	{
		if (pball->getDirection().y > 0)
			normalVec = Vector3(1, 0, 0);
		else
			normalVec = Vector3(0, 1, 0);
	}
	

	Vector3 normarDotp = normalVec * pball->getDirection().dotp(normalVec);

	pball->setDirection(pball->getDirection() - (2 * normarDotp));

	colBlock->decreaseLife(pball->getPower()); //충돌한 블록이 벽, 바가 아니면 라이프 감소

	if (colBlock->getLife() == 0)
		this->bCount -= 1;

}

void GameScene::roadStage(int stage)
{
	WCHAR* stagetxt = new WCHAR[20];
	switch(stage)
	{
	case 1:
		lstrcpy(stagetxt, _T("stage/stage1"));
		break;
	case 2:
		lstrcpy(stagetxt, _T("stage/stage2"));
		break;
	case 3:
		lstrcpy(stagetxt, _T("stage/stage3"));
		break;
	case 4:
		lstrcpy(stagetxt, _T("stage/stage4"));
		break;
	default:
		break;
	}
	FILE* pLoadFile = _tfopen(stagetxt, _T("r"));

	if (pLoadFile == NULL)
		exit(1);
	this->bCount = 0;
	fread(&bCount, sizeof(int), 1, pLoadFile);

	for (int i = 0; i < bCount; i++)
	{
		BlockData blockdata;
		fread(&blockdata, sizeof(BlockData), 1, pLoadFile);

		Block* block = dataToBlock(blockdata);
		blockList.insert(pair<int, Block*>(i + 5, block));
	}

	fclose(pLoadFile);
	delete[] stagetxt;
}

void GameScene::gameClear()
{
	pball->setDirection(Vector3(0, 0, 0));
	this->toTitle = this->currStage;
}

void GameScene::gameOver()
{
	pball->setSpeed(0);
	pball->setPosition(Vector3(-100, -100, 0));
	
	this->toTitle = 0;
}