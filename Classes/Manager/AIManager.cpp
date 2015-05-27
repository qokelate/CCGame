//
//  AIManager.cpp
//  diaoGame
//
//  Created by sma11case on 5/16/15.
//
//

#include "AIManager.h"
#include "../Base/Role/Role.h"
#include "../Base/Role/Mercenary.h"

AIManager::~AIManager()
{
	if (mHolder) mHolder->release();
}

void AIManager::setHolder(Role *holder)
{ 
	if (mHolder) mHolder->release();
	holder->retain();
	mHolder = holder;
}

void AIManager::randomMovement()
{
    USIZE n = (USIZE)(rand_0_1() * 10000) % 100;
    
    if (lastState && lastState <= 5)
    {
        stateCount += 1;
        if (stateCount < 100) n = lastState;
        else stateCount = 0;
    }
    
    lastState = n;
    
    switch (n)
    {
        case 1:
            mHolder->idle();
            break;
            
        case 2:
            if (mHolder->getPositionX() >= VALID_MIN_MAP_X-1000.0f) mHolder->walk(DIRECT_WALK_LEFT);
            break;
            
        case 3:
            if (mHolder->getPositionX() <= VALID_MAX_MAP_X+1000.0f) mHolder->walk(DIRECT_WALK_RIGHT);
            break;
            
        case 4:
            if (mHolder->getPositionX() >= VALID_MIN_MAP_X-1000.0f) mHolder->run(DIRECT_RUN_LEFT);
            break;
            
        case 5:
            if (mHolder->getPositionX() <= VALID_MAX_MAP_X+1000.0f) mHolder->run(DIRECT_RUN_RIGHT);
            break;
    }
}

void AIManager::randomJump()
{
    USIZE n = (USIZE)(rand_0_1() * 10000) % 100;
    if (n < 3) mHolder->jump();
}

void AIManager::randomAttack()
{
    USIZE n = (USIZE)(rand_0_1() * 1000000) % 1000;
    
    if (n < 10) ((Mercenary *)mHolder)->attack();
}

void AIManager::randomSkill()
{
    USIZE n = (USIZE)(rand_0_1() * 1000000) % 1000;
    
    if (n < 10)  ((Mercenary *)mHolder)->skill(0);
}

void AIManager::autoMode()
{
    randomMovement();
    if (ROLE_NONE == mHolder->getRoleType()) return;
    
    randomJump();
    randomAttack();
    randomSkill();
}

