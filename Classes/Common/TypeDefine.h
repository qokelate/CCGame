//
//  Common/TypeDefine.h
//  MyCppGame
//
//  Created by sma11case on 5/12/15.
//
//

#ifndef MyCppGame_TypeDefine_h
#define MyCppGame_TypeDefine_h
#include "EnumType.h"

typedef unsigned long USIZE;
typedef bool(*PF_EventDispatcher)(void *sender, StateEventType event, EffectState state, void *userParam);

typedef struct _ActionToken
{
	bool walkLeft = false;
	bool walkRight = false;
	bool runLeft = false;
	bool runRight = false;
	bool jump = false;
	bool attack = false;
	bool skill = false;
}ActionToken, *PActionToken;

#endif
