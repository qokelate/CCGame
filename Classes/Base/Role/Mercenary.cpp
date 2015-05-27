//
//  Mercenaries.cpp
//  MyCppGame
//
//  Created by sma11case on 5/12/15.
//
//

#include "Mercenary.h"

bool Mercenary::init()
{
    Role::init();
    setComment("Mercenary allocated");

#if GAME_DEBUG_MODE <= DBG_SHOW_ALLOCATE
    CONLOG("ptr=%p %s", this, getComment());
#endif
    return true;
}

bool Mercenary::initWithType(RoleType type)
{
    setRoleType(type);
	setCampType(CAMP_BADDY);
	setEventDispatcher(cbEventDispatcher, this);
    
#if GAME_DEBUG_MODE <= DBG_SHOW_TIPS
    CONLOG("ptr=%p RoleType=%d", this, getRoleType());
#endif
    
    initWithSpriteFrameName("stand.png");
    
    // 无动作状态
    {
//		auto animation = AnimationManager::getImageAnimationWithPlist("res/GameBasic.plist", "carrot_attack (%ld).png", 1, 18, "res/GameBasic.png");
        auto animation = AnimationManager::getAnimationWithCacheNamed("stand (%ld).png", 1, 15);
        animation->setDelayPerUnit(0.03f);
        animation->setLoops(1);
        animation->setRestoreOriginalFrame(false);
        animation->retain();
        
        auto animate = Animate::create(animation);
        animate->retain();
        setIdleAnimate(animate);
    }
    
    // 慢步状态
    {
//		auto animation = AnimationManager::getImageAnimationWithPlist("res/GameBasic.plist", "carrot_walk (%ld).png", 1, 18, "res/GameBasic.png");
        auto animation = AnimationManager::getAnimationWithCacheNamed("walk (%ld).png", 1, 19);
        animation->setDelayPerUnit(0.03f);
        animation->setLoops(1);
        animation->setRestoreOriginalFrame(false);
        animation->retain();
        
        auto animate = Animate::create(animation);
        animate->retain();
        setWalkAnimate(animate);
    }
    
    // 奔跑状态
    {
//		auto animation = AnimationManager::getImageAnimationWithPlist("res/GameBasic.plist", "carrot_walk (%ld).png", 1, 18, "res/GameBasic.png");
        auto animation = AnimationManager::getAnimationWithCacheNamed("walk (%ld).png", 1, 19);
        animation->setDelayPerUnit(0.03f);
        animation->setLoops(1);
        animation->setRestoreOriginalFrame(false);
        animation->retain();
        
        auto animate = Animate::create(animation);
        animate->retain();
        setRunAnimate(animate);
    }
    
    // 跳跃状态
    {
        auto animation = AnimationManager::getImageAnimationWithPlist("res/GameBasic.plist", "carrot_walk (%ld).png", 1, 18, "res/GameBasic.png");
//        auto animation = AnimationManager::getAnimationWithCacheNamed("walk (%ld).png", 1, 19);
        animation->setDelayPerUnit(0.03f);
        animation->setLoops(1);
        animation->setRestoreOriginalFrame(false);
        animation->retain();
        
        auto animate = Animate::create(animation);
        animate->retain();
        setJumpAnimate(animate);
    }
    
    // 武器初始化
    {
		auto animation = AnimationManager::getImageAnimationWithPlist("res/character_res.plist", "hoe (%d).png", 1, 15, "character_res.png");
//        auto animation = AnimationManager::getAnimationWithCacheNamed("hoe (%d).png", 1, 15);
		animation->setDelayPerUnit(0.03f);
        animation->setLoops(1);
        animation->setRestoreOriginalFrame(true);
        animation->retain();
        
        auto animate = Animate::create(animation);

        mAttackSprite = AnimateSprite::create();
        mAttackSprite->retain();
        
        mAttackSprite->initWithSpriteFrameName("hoe.png");
        mAttackSprite->setAnimate(animate);
    }
    
    setHp(100);
    setRunSpeed(5.0f);
    setWalkSpeed(3.0f);
    setJumpSpeed(5.0f);
    setJumpScope(100.0f);
    setAnchorPoint(Vec2(0.5f, 0.0f));
    
    return true;
}

void Mercenary::setUserControl(bool flag)
{
#if GAME_DEBUG_MODE <= DBG_SHOW_CHGSTATE
    CONLOG("ptr=%p Mercenary: UserControl: %d", this, flag);
#endif
    
    Role::setUserControl(flag);
    if (flag)
        mAttackSprite->setColor(ccc3(128,128,128));
    else
        mAttackSprite->setColor(ccc3(255,255,255));
}

void Mercenary::start()
{
#if GAME_DEBUG_MODE <= DBG_SHOW_CHGSTATE
    CONLOG("ptr=%p Mercenary::start()", this);
#endif
	Role::start();
	schedule(schedule_selector(Mercenary::updater));
}

void Mercenary::setFaceLeft(bool flag)
{
#if GAME_DEBUG_MODE <= DBG_SHOW_CHGSTATE
    CONLOG("ptr=%p Mercenary::setFaceLeft()", this);
#endif
    
    Role::setFaceLeft(flag);
    mAttackSprite->setFlippedX(flag);
    setPosition(getPosition());
}

void Mercenary::setPosition(const Vec2& pos)
{
#if GAME_DEBUG_MODE <= DBG_SHOW_CHGSTATE
    CONLOG("ptr=%p Mercenary::setPosition(%f, %f)", this, pos.x, pos.y);
#endif
    Role::setPosition(pos);
    float x = (isFaceLeft() ? -1 : 1) * 5.0f;
    mAttackSprite->setPositionX(x);
    float y = 15.0f;
    mAttackSprite->setPosition(pos + Vec2(x, y));
}

void Mercenary::setAnchorPoint(const Vec2 &anchor)
{
#if GAME_DEBUG_MODE <= DBG_SHOW_CHGSTATE
    CONLOG("ptr=%p Mercenary::setAnchorPoint(%f, %f)", this, anchor.x, anchor.y);
#endif
    Role::setAnchorPoint(anchor);
    if (mAttackSprite) mAttackSprite->setAnchorPoint(anchor);
}

void Mercenary::attachToLayer(Layer *layer, int zOrder)
{
    setLayer(layer);
    setZOrder(zOrder);
    layer->addChild(this, zOrder);
    layer->addChild(mAttackSprite, zOrder);
}

void Mercenary::attack()
{
	if (EFFECT_NONE != mAttackState) return;

	mAttackState = EFFECT_PLAYING;
    
    SimpleAudioEngine::sharedEngine()->playEffect("res/sound/sound_fight_attack.mp3");

    auto animate = mAttackSprite->getAnimate();
    auto finished = CallFunc::create([&]{
        mAttackState = EFFECT_STOP;
    });
    
    animate->retain();
    finished->retain();
    auto seq = Sequence::create(animate, finished, NULL);
    
    updateAttack(EFFECT_START);
    mAttackSprite->runAction(seq);
}

void Mercenary::updateAttack(EffectState state)
{
    switch (state)
    {
	case EFFECT_START:
		mEventDispatcher(this, EVENT_ATTACK, EFFECT_START, mEventDispatcherParam);
		break;

        case EFFECT_PLAYING:
			mEventDispatcher(this, EVENT_ATTACK, EFFECT_PLAYING, mEventDispatcherParam);
            break;
            
        case EFFECT_STOP:
            mAttackState = EFFECT_NONE;
			mEventDispatcher(this, EVENT_ATTACK, EFFECT_STOP, mEventDispatcherParam);
            mAttackSprite->stopAllActions();
            break;
    }
}

void Mercenary::skill(long index)
{
	if (mSkillBusy) return;

	mSkillBusy = true;
    
    bool isFL = isFaceLeft();

    auto skillSprite = Skill::create();
    
    skillSprite->initWithIndex(this, 0, isFL, true);
    skillSprite->setComment("skill");
    
    float x = NEG_POS(isFL) * (getContentSize().width/2 - 30.0f);
    skillSprite->setPosition(getPosition() + Vec2(x, getContentSize().height/2));
    skillSprite->setScale(0.3f, 0.3f);
    
    skillSprite->setEventDispatcher(mEventDispatcher);
    
    Layer *layer = getLayer();
    int zOrder = getZOrder();
    layer->addChild(skillSprite, zOrder);
    
    mSkillingList.push_back(skillSprite);
}

void Mercenary::updateSkill(EffectState state)
{
#if 0
    switch (state)
    {
	case EFFECT_START:
		mEventDispatcher(this, EVENT_SKILL, EFFECT_START, mEventDispatcherParam);
		break;

        case EFFECT_PLAYING:
			mEventDispatcher(this, EVENT_SKILL, EFFECT_PLAYING, mEventDispatcherParam);
            break;
            
        case EFFECT_STOP:
            mSkillState = EFFECT_NONE;
			mEventDispatcher(this, EVENT_SKILL, EFFECT_STOP, mEventDispatcherParam);
            AnimateSprite *as = (AnimateSprite *)*(--(mSkillingList.end()));
            as->removeFromParent();
            as->release();
            mSkillingList.pop_back();
            break;
    }
#endif
}

void Mercenary::addEquip(Equip *)
{
    
}
void Mercenary::removeEquip(Equip *)
{
    
}
void Mercenary::removeEquipWithIndex(USIZE index)
{
    
}

void Mercenary::updater(float dt)
{
	updateAttack(mAttackState);
	if (isUserControl()) return;
    
}