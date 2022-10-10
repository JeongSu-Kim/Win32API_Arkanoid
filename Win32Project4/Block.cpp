#include "stdafx.h"
#include "Block.h"

Block::Block()
{
	this->pen = NULL;
	this->brush = NULL;
	this->position = { 0, 0, 0 };
	this->width = 0;
	this->height = 0;
	this->life = 0;

	this->penStyle = 0;//
	this->penWidth = 0;//
	this->penColor = NULL;//
	this->brushColor = NULL;//
}

Block::Block(int posx, int posy, int width, int height, int life, COLORREF Color)
{
	this->pen = NULL;
	this->brush = NULL;

	this->position = { (float)posx, (float)posy, 0.0f };
	this->width = width;
	this->height = height;
	this->life = life;

	this->setBrush(Color);
	this->setLife(life);
}

Block::Block(const Block& other)
{
	this->position = { other.position.x, other.position.y, 0 };
	this->width = other.width;
	this->height = other.height;
	this->life = other.life;

	this->setPen(other.penStyle, other.penWidth, other.penColor);
	this->setBrush(other.brushColor);
}

Block::~Block()
{
	if (this->pen != NULL)
		DeleteObject(this->pen);
	if (this->brush != NULL)
		DeleteObject(this->brush);
}

//void Block::setHWnd(HWND hWnd)
//{
//	this->hWnd = hWnd;
//}

void Block::setPen(int iStyle, int cWidth, COLORREF color)
{
	if (this->pen != NULL)
		DeleteObject(this->pen);

	this->pen = CreatePen(iStyle, cWidth, color);

	this->penStyle = iStyle;//
	this->penWidth = cWidth;//
	this->penColor = color;//
}

void Block::setBrush(COLORREF color)
{
	if (this->brush != NULL)
		DeleteObject(this->brush);

	this->brush = CreateSolidBrush(color);

	this->brushColor = color;//
}

void Block::setHBrush(int style, COLORREF color)
{
	if (this->brush != NULL)
		DeleteObject(this->brush);

	this->brush = CreateHatchBrush(style, color);

	this->brushColor = color;
}

void Block::setPosition(int x, int y)
{
	this->position.x = x;
	this->position.y = y;
	this->position.z = 0;
}

void Block::setPosition(Vector3 pos)
{
	this->position = pos;
}

void Block::setPosition_x(int x)
{
	this->position.x = x;
}

void Block::setPosition_y(int y)
{
	this->position.y = y;
}

void Block::setSize(float width, float height)
{
	this->width = width;
	this->height = height;
}

void Block::setLife(int life)
{
	this->life = life;

	COLORREF penColor;
	switch (life)
	{
	case 1:
		this->setPen(BS_SOLID, 2, RGB(250, 250, 250)); //white
		break;
	case 2:
		this->setPen(BS_SOLID, 2, RGB(165, 113, 100)); //blonze
		break;
	case 3:
		this->setPen(BS_SOLID, 2, RGB(192, 192, 192)); //silver
		break;
	case 4:
		this->setPen(BS_SOLID, 2, RGB(255, 215, 0)); //gold
		break;
	default:
		break;
	}

}

void Block::decreaseLife(int damage)
{
	if (this->life > 0)
	{
		if (this->life >= damage)
			this->setLife(this->life - damage);
		else
			this->setLife(0);
	}
}

void Block::setSpeed(float speed)
{
	this->speed = speed;
}

Vector3 Block::getPosition()
{
	return this->position;
}

RECT Block::getRect()
{
	RECT rect;
	rect.left = position.x - width / 2;
	rect.top = position.y - height / 2;
	rect.right = position.x + width / 2;
	rect.bottom = position.y + height / 2;

	return rect;
}

int Block::getLife()
{
	return this->life;
}

float Block::getSpeed()
{
	if(this->speed != NULL)
		return this->speed;
}

void Block::draw(HDC hdc)
{
	HPEN oldPen = (HPEN)SelectObject(hdc, this->pen);
	HBRUSH oldBrush = (HBRUSH)SelectObject(hdc, this->brush);

	Rectangle(hdc, position.x - width / 2, position.y - height / 2, position.x + width / 2, position.y + height / 2);

	SelectObject(hdc, oldPen);
	SelectObject(hdc, oldBrush);
}

COLORREF Block::getBruhColor()
{
	return this->brushColor;
}

void PlayerBar::moveRight(float distance)
{
	this->position.x += distance;
}

void PlayerBar::moveLeft(float distance)
{
	this->position.x -= distance;
}

void Ball::draw(HDC hdc)
{
	HPEN oldPen = (HPEN)SelectObject(hdc, this->pen);
	HBRUSH oldBrush = (HBRUSH)SelectObject(hdc, this->brush);

	Ellipse(hdc, position.x - width / 2, position.y - height / 2, position.x + width / 2, position.y + height / 2);

	SelectObject(hdc, oldPen);
	SelectObject(hdc, oldBrush);
}

void Ball::move(Vector3 direction, float distance)
{
	this->position = this->position + (direction * distance);
}

void Ball::attach()
{
	this->attached = true;
}

void Ball::detach()
{
	this->attached = false;

}

bool Ball::isAttached()
{
	return this->attached;
}

void Ball::setDirection(Vector3 direction)
{
	this->direction = direction;
}

Vector3 Ball::getDirection()
{
	return this->direction;
}

void Ball::setPower(int power)
{
	this->power = power;
}

int Ball::getPower()
{
	return this->power;
}

int Ball::getRadius()
{
	return this->width / 2;
}
