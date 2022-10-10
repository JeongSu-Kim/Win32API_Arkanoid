#include "stdafx.h"
#include "MapEditor.h"

BlockData blockToData(Block* block)
{
	BlockData data;
	data.width = block->getRect().right - block->getRect().left;
	data.height = block->getRect().bottom - block->getRect().top;
	data.life = block->getLife();
	data.brushColor = block->getBruhColor();
	data.position = block->getPosition();

	return data;
}

Block* dataToBlock(BlockData data)
{
	Block* block = new Block;
	block->setSize(data.width, data.height);
	block->setLife(data.life);
	block->setBrush(data.brushColor);
	block->setPosition(data.position);

	return block;
}