//
//  Skill.cpp
//  MyCppGame
//
//  Created by sma11case on 5/12/15.
//
//

#include "Skill.h"
#include "../Base/Role/Mercenary.h"

bool Skill::init()
{
    Sprite::init();
    return true;
}

bool Skill::initWithIndex(Mercenary *holder, USIZE index, bool isFaceLeft, bool needLock)
{
    mIndex = index;
    mLockState = needLock;
    mHolder = holder;
    
    setFlippedX(isFaceLeft);
	retain();
    
    mSoundId = SimpleAudioEngine::sharedEngine()->playEffect("res/sound/sound_skill_30003.mp3");
    
    auto animation = AnimationManager::getImageAnimationWithPlist("res/VioletFire.plist", "%ld.png", 0, 3, nullptr);
    animation->retain();
    animation->setDelayPerUnit(0.03f);
    animation->setLoops(1);
    animation->setRestoreOriginalFrame(false);
    
    auto animate = Animate::create(animation);
    animate->retain();
    
    mNormal = animate;
    mAttacked = animate;
    mDestory = animate;
    
    auto move = MoveBy::create(2.0f, Vec2((isFaceLeft?-1:1)*150.0f, 0.0f));
    auto finished = CallFunc::create([&]{
        mPlayingState = EFFECT_STOP;
    });
    
    move->retain();
    finished->retain();
    auto seq = Sequence::create(move, finished, NULL);
    runAction(seq);
    
    mPlayingState = EFFECT_START;
    schedule(schedule_selector(Skill::updater));

	return true;
}

void Skill::updater(float dt)
{
    Action *temp = nullptr;

    switch (mPlayingState)
    {
        case EFFECT_START:
            mPlayingState = EFFECT_PLAYING;
            if (mLockState) mHolder->setSkillBusy(true);
            temp = runAction(RepeatForever::create(mNormal));
            temp->setTag(ID_ACTION_SKILLING);
            mEventDispatcher(mHolder, EVENT_SKILL, EFFECT_START, this);
            break;
            
        case EFFECT_PLAYING:
            mEventDispatcher(mHolder, EVENT_SKILL, EFFECT_PLAYING, this);
            break;
            
        case EFFECT_STOP:
            removeFromParent();
            stopAllActions();
            SimpleAudioEngine::sharedEngine()->stopEffect(mSoundId);
//            if (mLockState) mHolder->setSkillBusy(false);
            unscheduleAllSelectors();
			mEventDispatcher(mHolder, EVENT_SKILL, EFFECT_STOP, this);
			if (mLockState) mHolder->setSkillBusy(false);            
			release();
            break;
    }
}
