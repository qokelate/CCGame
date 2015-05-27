#ifndef _GAME_ROOT_H_
#define _GAME_ROOT_H_

#include "cocos2d.h"
using namespace cocos2d;

#include "Scene/SceneGame.h"
#include "Manager/ConfigManager.h"

class GameRoot
{
public :
    ~GameRoot();
	static void InitializeResource();
	static SceneGame* getSceneGame();

private :
	static SceneGame* mSceneGame;
};

#endif