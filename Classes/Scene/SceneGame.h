//
//  SceneGame.h
//  GMO
//
//  Created by amos on 15/5/7.
//
//

#ifndef __GMO__SceneGame__
#define __GMO__SceneGame__

#include "cocos2d.h"
#include "HudLayer.h"
#include "GameLayer.h"
#include "../Common/Common.h"
#include "../Manager/RoleManager.h"
#include "SimpleAudioEngine.h"

using namespace CocosDenshion;
using namespace cocos2d;

class SceneGame : public Scene
{
public :
    SceneGame();
    bool init();
    ~SceneGame();
    
private :
    HudLayer* mHudLayer;
    GameLayer* mGameLayer;
    
    void broadcastInput(float dt);
};

#endif /* defined(__GMO__SceneGame__) */
