#include "stdafx.h"
#include "fps.h"

#include <stdio.h>
#include <tchar.h>

FPScount::FPScount()
{
	this->targetFPS = 60;
}

FPScount::FPScount(int fps)
{
	this->targetFPS = fps;
}

FPScount::~FPScount()
{

}

void FPScount::init()
{
	currentFPS = 0;
	frameCount = 0;
	oneFrameTime = 0;
	sleepTime = 1.0f / targetFPS * 1000;
	currTime = 0;
	prevTime = GetTickCount();
	oneSecondTime = GetTickCount();
}

void FPScount::update()
{
	currTime = GetTickCount();
	oneFrameTime = (float)(currTime - prevTime) / 1000;
	sleepTime = 1.0f / targetFPS * 1000;

	//cout << oneFrameTime << endl;

	if (currTime - oneSecondTime > 1000)
	{
		currentFPS = frameCount;
		//cout << "FPS : " << currentFPS << endl;
		frameCount = 0;
		oneSecondTime = GetTickCount();
	}
	else
	{
		if (oneFrameTime == 0)
		{
			oneFrameTime = 1.0f / targetFPS;
		}
		else if (currTime - prevTime < 1.0f / targetFPS)
		{
			cout << "<<<<" << endl;
			sleepTime += currTime - prevTime;
		}
	}

	prevTime = currTime;

	Sleep(sleepTime);
	frameCount++;
}

int FPScount::getFPS()
{
	return currentFPS;
}

float FPScount::getOneFrameTime()
{
	return oneFrameTime;
}
