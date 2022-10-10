#pragma once
#include "stdafx.h"
#include "Block.h"

struct BlockData
{
	int width;
	int height;
	int life;

	COLORREF brushColor;

	Vector3 position;
};

BlockData blockToData(Block * block);

Block * dataToBlock(BlockData data);
