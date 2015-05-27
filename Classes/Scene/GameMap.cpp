#include "GameMap.h"
#include "../Common/Common.h"

const float FLOOR_POS_Y = 110;
const float CELL_POS_Y = 220;
const float BG_WIDTH = 1100;
const float LEFT_EDGE_X = -BG_WIDTH / 2 + WIN_WIDTH / 2;
const float RIGHT_EDGE_X = BG_WIDTH / 2 + WIN_WIDTH / 2;

GameMap::GameMap()
	: mWalkableMapMinX(LEFT_EDGE_X), mWalkableMapMaxX(RIGHT_EDGE_X), 
	mWalkableMapMinY(FLOOR_POS_Y), mWalkableMapMaxY(CELL_POS_Y)
{
	Sprite::initWithSpriteFrameName("background.png");

	init();
}

bool GameMap::init()
{
	//CCSprite::init();

	return true;
}

int GameMap::getWalkableRight()
{
	return mWalkableMapMaxX;
}

int GameMap::getWalkableTop()
{
	return mWalkableMapMaxY;
}

int GameMap::getWalkableLeft()
{
	return mWalkableMapMinX;
}

int GameMap::getWalkableBottom()
{
	return mWalkableMapMinY;
}