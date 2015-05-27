//
//  AnimateSprite.h
//  MyCppGame
//
//  Created by sma11case on 5/13/15.
//
//

#ifndef __MyCppGame__AnimateSprite__
#define __MyCppGame__AnimateSprite__

#include <stdio.h>
#include "../Common/Common.h"

class AnimateSprite: public Sprite
{
public:
    ALLOCATE(AnimateSprite, "AnimateSprite");
    RELEASE2(AnimateSprite, "AnimateSprite");

    CREATE_FUNC(AnimateSprite);
    virtual bool init();
    
    virtual void setAnimate(Animate *ani);
    virtual Action* playAnimate();
    
#if GAME_DEBUG_MODE <= DBG_SHOW_OVERRIDE
    virtual void setPosition(const Vec2& pos) override;
    virtual void setAnchorPoint(const Vec2 &anchor) override;
#endif
    
    ADDGETTER(Animate*, mAnimate, getAnimate);
    CC_SYNTHESIZE(char*, mComment, Comment);
private:
    Animate *mAnimate = nullptr;
};

#endif /* defined(__MyCppGame__AnimateSprite__) */
