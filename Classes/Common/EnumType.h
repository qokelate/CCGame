//
//  Common/EnumType.h
//  MyCppGame
//
//  Created by sma11case on 5/13/15.
//
//

#ifndef MyCppGame_EnumType_h
#define MyCppGame_EnumType_h

// Role回调事件类型
enum StateEventType
{
	EVENT_UNKNOW = 0,
	EVENT_JUMP,
	EVENT_ATTACK,
	EVENT_SKILL,
};

// 天赋类型
enum Talent
{
	TALENT_NONE = 0,
};

// 阵营类型
enum CampType
{
    CAMP_NONE = 0,
	CAMP_PLAYER,
	CAMP_FRIEND,
	CAMP_BADDY,
};

// 兵种类型
enum RoleType
{
    ROLE_NONE = 0,
	ROLE_WARRIOR,
};

// 攻击类型
enum AttackType
{
	ATTACK_NORMAL = 0,
};

// 摇杆事件
enum InDirState
{
	IN_DIR_NO_PRESSED = 0,
	IN_DIR_UP,
	IN_DIR_DOWN,
	IN_DIR_LEFT,
	IN_DIR_RIGHT,
};

// 按键事件
enum InBtnState
{
	IN_BTN_PRESSED,
	IN_BTN_NO_PRESSED
};

// 动作状态(躯体)
enum BodyState
{
	BODY_NONE = 0,
	BODY_IDLE,
	BODY_WALK,
	BODY_RUN,
	BODY_HURT,
	BODY_DIE,
	BODY_JUMP,
	BODY_MOVING
};

// 动作状态(动作)
enum ActionState
{
	ACT_IDLE = 0,
	ACT_ATTACK,
	ACT_SKILL,
};

// 作用状态
enum EffectState
{
	EFFECT_NONE = 0,
	EFFECT_START,
	EFFECT_PLAYING,
	EFFECT_STOP,
};

// 移动状态
enum MovingState
{
	MOVING_UNKNOW = 0,
	MOVING_NONE,
	MOVING_WALK,
	MOVING_RUN,
};

// 移动方向
enum DirectState
{
	DIRECT_NONE = 0,
	DIRECT_WALK_LEFT,
	DIRECT_WALK_RIGHT,
	DIRECT_RUN_LEFT,
	DIRECT_RUN_RIGHT
};

// 武器状态
enum WeaponState
{
	WEAPON_READY,
	WEAPON_COOLING,
	WEAPON_USING
};

#endif
