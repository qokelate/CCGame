#ifndef _GAME_MAP_H_
#define _GAME_MAP_H_

#include "cocos2d.h"
USING_NS_CC;

class GameMap : public Sprite
{
public :
	GameMap();
	bool init();
	
	int getWalkableRight();
	int getWalkableTop();
	int getWalkableLeft();
	int getWalkableBottom();

private :
	const int mWalkableMapMinX;
	const int mWalkableMapMaxX;
	const int mWalkableMapMinY;
	const int mWalkableMapMaxY;
};

#endif