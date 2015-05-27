//
//  CommonConfig.h
//  MyCppGame
//
//  Created by sma11case on 5/13/15.
//
//

#ifndef __MyCppGame__CommonConfig__
#define __MyCppGame__CommonConfig__

#include <stdio.h>
#include "../Common/Macros.h"
#include "cocos2d.h"
#include "BaseManager.h"
#include "../Manager/BufferManager.h"
#include "../Common/DebugHelper.h"

class Role;
class RoleManager;

using namespace cocos2d;

class ConfigManager
{
public:
	ALLOCATE(ConfigManager, "ConfigManager");
	RELEASE(ConfigManager, "ConfigManager");
    CC_SYNTHESIZE(Layer *, mMapLayer, MapLayer);
    CC_SYNTHESIZE(Layer *, mGameLayer, GameLayer);
    CC_SYNTHESIZE(Layer *, mHudLayer, HudLayer);
    CC_SYNTHESIZE(Scene *, mMissionScene, MissionScene);
    
    CC_SYNTHESIZE(RoleManager*, mRoleManager, RoleManager);
    CC_SYNTHESIZE(BufferManager*, mBufferManager, BufferManager);
    
    void setUnderControl(Role* obj);
    ADDGETTER(Role*, mUnderControl, getUnderControl);
    
private:
    Role *mUnderControl = nullptr;
};

#endif /* defined(__MyCppGame__CommonConfig__) */
