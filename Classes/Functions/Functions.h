//
//  Functions.h
//  diaoGame
//
//  Created by sma11case on 5/14/15.
//
//

#ifndef __diaoGame__Functions__
#define __diaoGame__Functions__

#include <stdio.h>
#include "../Common/Common.h"

Sprite* maskedSprite(Sprite* mask, Sprite* sprite);

bool npcEvent(void *sender, StateEventType event, EffectState state, void *userParam);
bool playerEvent(void *sender, StateEventType event, EffectState state, void *userParam);
bool cbEventDispatcher(void *sender, StateEventType event, EffectState state, void *userParam);

#endif /* defined(__diaoGame__Functions__) */
