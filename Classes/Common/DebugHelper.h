//
//  DebugHelper.h
//  diaoGame
//
//  Created by sma11case on 5/16/15.
//
//

#ifndef diaoGame_DebugHelper_h
#define diaoGame_DebugHelper_h
#include "Macros.h"

// 调试日志显示级别
enum DebugLevel
{
    DBG_SHOW_OVERRIDE = 1000, // 无动作override
    DBG_SHOW_ALLOCATE = 2000, // 内存申请
    DBG_SHOW_RELEASE = 3000, // 内存释放
    DBG_SHOW_CHGSTATE = 4000, // 状态改变
    DBG_SHOW_TIPS = 5000, // 数量不多的提示文字
};

#define GAME_DEBUG_MODE 0

#ifdef COCOS2D_DEBUG
#undef GAME_DEBUG_MODE
#define GAME_DEBUG_MODE 5000
#endif

// 打开/关闭日志显示
#if GAME_DEBUG_MODE
#define SHOW_DEBUG_LOG 1
#define CONLOG(format, ...) do{ printf(format, ##__VA_ARGS__);printf("\n");} while(false)
#else
#define SHOW_DEBUG_LOG 0
#define CONLOG(...) do{}while(false)
#endif

#if GAME_DEBUG_MODE <= DBG_SHOW_ALLOCATE
#define ALLOCATE(ClassType, ClassName) ClassType(){CONLOG("ptr=%p %s allocated", this, ClassName);}
#else
#define ALLOCATE(ClassType, ClassName)
#endif

#if GAME_DEBUG_MODE <= DBG_SHOW_RELEASE
#define RELEASE(ClassType, ClassName) ~ClassType(){CONLOG("ptr=%p %s released", this, ClassName);}
#define RELEASE2(ClassType, ClassName) ~ClassType(){CONLOG("ptr=%p %s released", this, (mComment?mComment:ClassName));}
#else
#define RELEASE(ClassType, ClassName)
#define RELEASE2(ClassType, ClassName) 
#endif

#define CREATE_INIT() virtual bool init(){return true;}

#endif
