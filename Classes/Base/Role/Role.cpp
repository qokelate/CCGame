//
//  Role.cpp
//  MyCppGame
//
//  Created by sma11case on 5/12/15.
//
//

#include "Role.h"

Role::~Role()
{
	stopAllActions();
	unscheduleAllSelectors();
	if (mAIManager) mAIManager->release();
	gConfigManager->getRoleManager()->remove(this);
}

bool Role::init()
{
    Sprite::init();
    
    setRoleType(ROLE_NONE);
	gConfigManager->getRoleManager()->add(this);

#if GAME_DEBUG_MODE
	setComment("Role allocated");
#endif
    
#if GAME_DEBUG_MODE <= DBG_SHOW_ALLOCATE
    CONLOG("ptr=%p %s", this, getComment());
#endif
    return true;
}

void Role::setFaceLeft(bool flag)
{
	setFlippedX(flag); 
	mIsFaceLeft = flag; 
}

void Role::setEventDispatcher(PF_EventDispatcher func, void *param)
{
	mEventDispatcher = func;
	mEventDispatcherParam = param;
}

void Role::setUserControl(bool flag)
{
#if GAME_DEBUG_MODE <= DBG_SHOW_CHGSTATE
    CONLOG("ptr=%p Role: UserControl: %d", this, flag);
#endif
    if (flag)
        setColor(ccc3(128, 128, 128));
    else
        setColor(ccc3(255, 255, 255));
    mIsUserMode = flag;
}

void Role::start()
{
#if GAME_DEBUG_MODE <= DBG_SHOW_CHGSTATE
    CONLOG("ptr=%p Role::start()", this);
#endif

	if (mAIManager) return;

	mAIManager = AIManager::create();
	mAIManager->retain();
	mAIManager->setHolder(this);

    mMovingState = MOVING_UNKNOW;
    idle();
    schedule(schedule_selector(Role::updater));
}

Vec2 Role::getMovingScope()
{
    float y = 0.0f;
    float x = 0.0f;
    switch (mMovingState)
    {
        case MOVING_WALK:
            x = getWalkSpeed();
            break;
            
        case MOVING_RUN:
            x = getRunSpeed();
            break;
    }
    
    return Vec2(x, y);
}

void Role::idle()
{
    if (mMovingState == MOVING_NONE) return;
    if (EFFECT_NONE != mJumpingState) return;
    
    mMovingState = MOVING_NONE;
    stopActionByTag(ID_ACTION_MOVING);
    auto temp = runAction(RepeatForever::create(getIdleAnimate()));
    temp->setTag(ID_ACTION_MOVING);
}

void Role::walk(DirectState dir)
{
    switch (dir)
    {
        case DIRECT_WALK_LEFT:
            if (!mIsFaceLeft) setFaceLeft(true);
            break;
            
        case DIRECT_WALK_RIGHT:
            if (mIsFaceLeft) setFaceLeft(false);
            break;

		default:
			return;
    }
    
    if (MOVING_WALK == mMovingState) return;
    if (EFFECT_NONE != mJumpingState) return;
    
    mMovingState = MOVING_WALK;
    stopActionByTag(ID_ACTION_MOVING);
    auto temp = runAction(RepeatForever::create(getWalkAnimate()));
    temp->setTag(ID_ACTION_MOVING);
}

void Role::run(DirectState dir)
{
    switch (dir)
    {
        case DIRECT_RUN_LEFT:
            if (!mIsFaceLeft) setFaceLeft(true);
            break;
            
        case DIRECT_RUN_RIGHT:
            if (mIsFaceLeft) setFaceLeft(false);
            break;

		default:
			return;
    }
    
    if (MOVING_RUN == mMovingState) return;
    if (EFFECT_NONE != mJumpingState) return;
    
    mMovingState = MOVING_RUN;
    stopActionByTag(ID_ACTION_MOVING);
    auto temp = runAction(RepeatForever::create(getRunAnimate()));
    temp->setTag(ID_ACTION_MOVING);
}

void Role::jump()
{
    if (EFFECT_NONE != mJumpingState) return;
    
    updateJumping(EFFECT_START);
}

void Role::updateJumping(EffectState state)
{
    bool doNext = false;
    float y = 0.0f;
    Action *temp = nullptr;
    switch (state)
    {
        case EFFECT_START:
            mJumpingState = EFFECT_PLAYING;
            stopActionByTag(ID_ACTION_MOVING);
            
            doNext = mEventDispatcher(this, EVENT_JUMP, EFFECT_START, mEventDispatcherParam);
            if (!doNext)
            {
                mJumpingState = EFFECT_STOP;
                break;
            }
            
            temp = runAction(RepeatForever::create(getJumpAnimate()));
            temp->setTag(ID_ACTION_JUMPING);
            mJumpingY = getJumpScope();
            break;
            
        case EFFECT_PLAYING:
            doNext = mEventDispatcher(this, EVENT_JUMP, EFFECT_PLAYING, mEventDispatcherParam);
            if (!doNext)
            {
                mJumpingState = EFFECT_STOP;
                break;
            }
            
            if (mJumpingY > 0)
            {
                y = getJumpSpeed();
                mJumpingY -= y;
                
                if (mJumpingY <= 0.0f) mJumpingY = -getJumpScope();
            }
            else
            {
                y = -getJumpSpeed();
                mJumpingY -= y;
                if (mJumpingY > 0.0f) mJumpingY = 0.0f;
            }
            
            if (0.0f == mJumpingY) mJumpingState = EFFECT_STOP;
            setPosition(getPosition() + Vec2(0.0f, y));
            break;
            
        case EFFECT_STOP:
            mJumpingState = EFFECT_NONE;
            stopActionByTag(ID_ACTION_JUMPING);
            mMovingState = MOVING_RUN;
            idle();
            mEventDispatcher(this, EVENT_JUMP, EFFECT_STOP, mEventDispatcherParam);
            break;
    }
}

void Role::updateMoving()
{
    Vec2 pos = getPosition();
    float x = pos.x;
    float y = pos.y;
    
    switch (mMovingState)
    {
        case MOVING_RUN:
            if (mIsFaceLeft) x -= getRunSpeed();
            else x += getRunSpeed();
            setPosition(Vec2(x, y));
            break;
            
        case MOVING_WALK:
            if (mIsFaceLeft) x -= getWalkSpeed();
            else x += getWalkSpeed();
            setPosition(Vec2(x, y));
            break;
    }
}

void Role::updater(float dt)
{
    updateJumping(mJumpingState);
    if (mIsUserMode) return;

	updateMoving();
    mAIManager->autoMode();
}

////////////////////////////////////////////////////////////////////////
#if GAME_DEBUG_MODE <= DBG_SHOW_OVERRIDE
void Role::setPosition(const Vec2& pos)
{
    CONLOG("ptr=%p Role::setPosition(%f, %f)", this, pos.x, pos.y);
    Sprite::setPosition(pos);
}

void Role::setAnchorPoint(const Vec2 &anchor)
{
    CONLOG("ptr=%p Role::setAnchorPoint(%f, %f)", this, anchor.x, anchor.y);
    Sprite::setAnchorPoint(anchor);
}
#endif


