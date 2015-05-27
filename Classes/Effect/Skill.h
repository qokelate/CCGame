//
//  Skill.h
//  MyCppGame
//
//  Created by sma11case on 5/12/15.
//
//

#ifndef __MyCppGame__Skill__
#define __MyCppGame__Skill__

#include <stdio.h>
#include "../Common/Common.h"
#include "../Effect/AnimateSprite.h"
#include "../Common/TypeDefine.h"
#include "SimpleAudioEngine.h"
#include "../Manager/AnimationManager.h"

using namespace CocosDenshion;
class Mercenary;

// 技能类
class Skill: public AnimateSprite
{
public:
    ALLOCATE(Skill, "Skill");
    RELEASE2(Skill, "Skill");    
    CREATE_FUNC(Skill);
    virtual bool init();

    virtual bool initWithIndex(Mercenary *holder, USIZE index, bool isFaceLeft, bool needLock);
    virtual void setEventDispatcher(PF_EventDispatcher func){mEventDispatcher = func;};
    
    CC_SYNTHESIZE(USIZE, mPhysicHurt, PhysicHurt); // 物伤
    CC_SYNTHESIZE(USIZE, mMagicHurt, MagicHurt); // 魔伤
    CC_SYNTHESIZE(USIZE, mExEffect, ExEffect); // 附加效果
    
    ADDGETTER(USIZE, mIndex, getIndex); // 第几号技能
    ADDGETTER(Mercenary*, mHolder, getHolder);
    ADDGETTER(bool, mLockState, isLockState);
    
protected:
    PF_EventDispatcher mEventDispatcher = nullptr;

private:
    void updater(float dt);
    
    Animate *mNormal; // 正常循环动画(命中前)
    Animate *mAttacked;  // 命中后动画(命中过程中)
    Animate *mDestory;   // 消失动画(命中后)
    
    Mercenary *mHolder = nullptr;
    USIZE mIndex = 0; // 哪个技能
    int mSoundId = 0; // 音效ID
    EffectState mPlayingState = EFFECT_NONE;
    bool mLockState = false; // 施放期间是否锁定
};

#endif /* defined(__MyCppGame__Skill__) */
