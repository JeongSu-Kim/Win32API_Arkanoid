#pragma once

#include "stdafx.h"

class FPScount
{
private:
	int targetFPS;
	int currentFPS;
	int frameCount;
	float oneFrameTime;
	float sleepTime;
	DWORD prevTime;
	DWORD currTime;
	DWORD oneSecondTime;

public:
	FPScount();
	FPScount(int fps);
	~FPScount();

	void init();
	void update();
	int getFPS();
	float getOneFrameTime();
};