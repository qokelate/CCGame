//
//  AIManager.h
//  diaoGame
//
//  Created by sma11case on 5/16/15.
//
//

#ifndef __diaoGame__AIManager__
#define __diaoGame__AIManager__

#include <stdio.h>
#include "../Common/Common.h"
#include "BaseManager.h"
#include "cocos2d.h"

class Role;
using namespace cocos2d;

class AIManager: public Ref
{
public:
    ALLOCATE(AIManager, "AIManager");
//    RELEASE(AIManager, "AIManager");
	~AIManager();
    CREATE_FUNC(AIManager);
    CREATE_INIT();
    
    virtual void autoMode(); // 人工智能
    virtual void randomJump(); // 蹦蹦又跳跳
    virtual void randomMovement(); // 到处乱跑
    virtual void randomAttack(); // 拿个铁锤招摇过市
    virtual void randomSkill(); // 妈蛋,有技能了
	virtual void setHolder(Role *holder);

private:
    Role *mHolder = nullptr;
    USIZE lastState = 0;
    USIZE stateCount = 0;
};

#endif /* defined(__diaoGame__AIManager__) */
