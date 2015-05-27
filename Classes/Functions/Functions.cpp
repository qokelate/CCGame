//
//  Functions.cpp
//  diaoGame
//
//  Created by sma11case on 5/14/15.
//
//

#include "Functions.h"
#include "../Base/Role/Role.h"

inline bool npcEvent(void *sender, StateEventType event, EffectState state, void *userParam)
{
//    CCLOG("NPC event=%d state=%d", event, state);
	return true;
}

inline bool playerEvent(void *sender, StateEventType event, EffectState state, void *userParam)
{
    switch (event)
    {
        case EVENT_JUMP:
            switch (state)
        {
            case EFFECT_START:
                CONLOG("jump start");
                break;
                
            case EFFECT_PLAYING:
                CONLOG("jumping");
                break;
                
            case EFFECT_STOP:
                CONLOG("jump stop");
                break;
        }
            break;
            
        case EVENT_ATTACK:
            switch (state)
        {
            case EFFECT_START:
                CONLOG("attack start");
                break;
                
            case EFFECT_PLAYING:
                CONLOG("attacking");
                break;
                
            case EFFECT_STOP:
                CONLOG("attack stop");
                break;
        }
            break;
            
        case EVENT_SKILL:
            switch (state)
        {
            case EFFECT_START:
                CONLOG("skill start");
                break;
                
            case EFFECT_PLAYING:
                CONLOG("skilling");
                break;
                
            case EFFECT_STOP:
                CONLOG("skill stop");
                break;
        }
            break;
    }
    
    return true;
}

bool cbEventDispatcher(void *sender, StateEventType event, EffectState state, void *userParam)
{
	CCASSERT(EVENT_UNKNOW != event, "UNKNOW EVENT!");

	Role *temp = (Role *)sender;
    
    bool retn = false;
	if (!temp->isUserControl()) retn = npcEvent(sender, event, state, userParam);
    else retn = playerEvent(sender, event, state, userParam);

	return retn;
}

inline Sprite* maskedSprite(Sprite* mask, Sprite* sprite)
{
    Size size = mask->getContentSize();
    RenderTexture* rt = RenderTexture::create(size.width, size.height);
    
    mask->setPosition(ccp(size.width/2, size.height/2));
    sprite->setPosition(ccp(sprite->getContentSize().width/2, sprite->getContentSize().height/2));
    
    ccBlendFunc func1 = {GL_ONE, GL_ZERO};
    ccBlendFunc func2 = {GL_DST_ALPHA, GL_ZERO};
    
    mask->setBlendFunc(func1);
    sprite->setBlendFunc(func2);
    
    rt->begin();
    mask->visit();
    sprite->visit();
    rt->end();
    
    Sprite* retval = Sprite::createWithTexture(rt->getSprite()->getTexture());
    retval->setFlipY(true);
    return retval;
}

