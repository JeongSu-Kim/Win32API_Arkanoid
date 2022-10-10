#pragma once
#pragma once
#include "stdafx.h"
#include <windows.h>
#include "Vector3.h"

class Block
{
protected:
	//HWND hWnd;
	HPEN pen;
	HBRUSH brush;
	//RECT rect;
	int width;
	int height;
	int life;
	float speed = 0.0f;

	int penStyle;//
	int penWidth;//
	COLORREF penColor;//
	COLORREF brushColor;//

	Vector3 position;

public:
	Block();
	Block(int posx, int posy, int width, int height, int life, COLORREF Color);
	Block(const Block& other);
	virtual ~Block();

	//void setHWnd(HWND hWnd);
	void setPen(int iStyle, int cWidth, COLORREF color);
	void setBrush(COLORREF color);
	void setHBrush(int style, COLORREF color); //
	void setPosition(int x, int y);
	void setPosition(Vector3 pos);
	void setPosition_x(int x);
	void setPosition_y(int y);
	void setSize(float width, float height);
	void setLife(int life);
	void decreaseLife(int damage);
	void setSpeed(float speed);

	Vector3 getPosition();
	RECT getRect();
	int getLife();
	float getSpeed();

	virtual void draw(HDC hdc);

	//int getPenStyle();
	//int getPenWidth();
	//COLORREF getPenColor();
	COLORREF getBruhColor();
};

class PlayerBar : public Block
{
private:
	float speed = 200.0f;
public:
	PlayerBar() { };
	PlayerBar(Vector3 pos) { this->position = pos; };
	virtual ~PlayerBar() { };

	void moveRight(float distance);
	void moveLeft(float distance);
};

class Ball : public Block
{
private:
	float speed = 200.0f;
	bool attached = true;
	Vector3 direction = Vector3(-1, -1, 0).normal();
	int power = 1;
public:
	Ball() { };
	Ball(Vector3 pos) { this->position = pos; };
	virtual ~Ball() { };

	virtual void draw(HDC hdc);

	void move(Vector3 direction, float distance);
	void attach();
	void detach();
	bool isAttached();

	void setDirection(Vector3 direction);
	Vector3 getDirection();

	void setPower(int power);
	int getPower();
	int getRadius();
};