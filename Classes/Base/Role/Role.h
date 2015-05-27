//
//  Role.h
//  MyCppGame
//
//  Created by sma11case on 5/12/15.
//
//

#ifndef __MyCppGame__Role__
#define __MyCppGame__Role__

#include <stdio.h>
#include "../../Common/Common.h"
#include "../../Effect/AnimateSprite.h"
#include "../../Functions/Functions.h"
#include "../../Manager/AIManager.h"
#include "../../Manager/RoleManager.h"

#define NEG_POS(x) (x ? -1 : 1)

class Role: public Sprite
{
public:
	Role(){};
	~Role();
    CREATE_FUNC(Role);
    virtual bool init();
    
    virtual void idle();
    virtual void jump();
    virtual void walk(DirectState dir);
    virtual void run(DirectState dir);
	virtual void start();
    virtual void setUserControl(bool flag);

	virtual void setFaceLeft(bool flag);
	virtual Vec2 getMovingScope();
	virtual void setEventDispatcher(PF_EventDispatcher func, void *param);
    
#if GAME_DEBUG_MODE <= DBG_SHOW_OVERRIDE
    virtual void setPosition(const Vec2& pos) override;
    virtual void setAnchorPoint(const Vec2 &anchor) override;
#endif
    
    CC_SYNTHESIZE(USIZE, mHp, Hp); // 生命值
    CC_SYNTHESIZE(Talent, mTalent, Talent); // 天赋类型
    CC_SYNTHESIZE(RoleType, mRoleType, RoleType); // 兵种类型
    CC_SYNTHESIZE(CampType, mCampType, CampType); // 阵营
    
    CC_SYNTHESIZE(Animate *, mIdleAnimate, IdleAnimate);
    CC_SYNTHESIZE(Animate *, mWalkAnimate, WalkAnimate);
    CC_SYNTHESIZE(Animate *, mRunAnimate, RunAnimate);
    CC_SYNTHESIZE(Animate *, mJumpAnimate, JumpAnimate);
    
    CC_SYNTHESIZE(float, mRunSpeed, RunSpeed);
    CC_SYNTHESIZE(float, mWalkSpeed, WalkSpeed);
    CC_SYNTHESIZE(float, mJumpSpeed, JumpSpeed);
    CC_SYNTHESIZE(float, mJumpScope, JumpScope);
    CC_SYNTHESIZE(char*, mComment, Comment);
    
    CC_SYNTHESIZE(Layer *, mLayer, Layer);
    CC_SYNTHESIZE(int, mZOrder, ZOrder);

	ADDGETTER(bool, mIsUserMode, isUserControl);
	ADDGETTER(bool, mIsFaceLeft, isFaceLeft);
	ADDGETTER(MovingState, mMovingState, getMovingState);

protected:
	PF_EventDispatcher mEventDispatcher = nullptr;
	void *mEventDispatcherParam = nullptr;

private:
    void updater(float dt);
    void updateJumping(EffectState state);
	void updateMoving();
    
	MovingState mMovingState = MOVING_UNKNOW; // 移动方向
	EffectState mJumpingState = EFFECT_NONE; // 跳跃状态
	bool mIsUserMode = false; // 是否为用户操作状态
	bool mIsFaceLeft = false; // 是否面向左边
    AIManager *mAIManager = nullptr; // AI管理器
    float mJumpingY = 0.0f; // 跳跃高度余量
};

#endif /* defined(__MyCppGame__Role__) */
