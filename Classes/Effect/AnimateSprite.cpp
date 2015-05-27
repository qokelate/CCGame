//
//  AnimateSprite.cpp
//  MyCppGame
//
//  Created by sma11case on 5/13/15.
//
//

#include "AnimateSprite.h"

bool AnimateSprite::init()
{
    Sprite::init();
    return true;
}

void AnimateSprite::setAnimate(Animate *ani)
{
    if (mAnimate) mAnimate->release();
    mAnimate = ani;
    if (mAnimate) mAnimate->retain();
}

Action* AnimateSprite::playAnimate()
{
    return runAction(mAnimate);
}

#if GAME_DEBUG_MODE <= DBG_SHOW_OVERRIDE
void AnimateSprite::setPosition(const Vec2& pos)
{
    CONLOG("ptr=%p AnimateSprite::setPosition(%f, %f)", this, pos.x, pos.y);
    Sprite::setPosition(pos);
}

void AnimateSprite::setAnchorPoint(const Vec2 &anchor)
{
    CONLOG("ptr=%p AnimateSprite::setAnchorPoint(%f, %f)", this, anchor.x, anchor.y);
    Sprite::setAnchorPoint(anchor);
}
#endif
