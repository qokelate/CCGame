//
//  Mercenaries.h
//  MyCppGame
//
//  Created by sma11case on 5/12/15.
//
//

#ifndef __MyCppGame__Mercenaries__
#define __MyCppGame__Mercenaries__

#include <stdio.h>
#include "../../Common/Common.h"
#include "Role.h"
#include "../Item/Weapon.h"
#include "../Item/Armor.h"
#include "../Item/Equip.h"
#include "../../Effect/Skill.h"
#include "../../Manager/AnimationManager.h"
#include "SimpleAudioEngine.h"

using namespace CocosDenshion;

using namespace std;

// 兵种
class Mercenary: public Role
{
public:
    ALLOCATE(Mercenary, "Mercenary");
    RELEASE2(Mercenary, "Mercenary");
    CREATE_FUNC(Mercenary);
    virtual bool init();
    virtual bool initWithType(RoleType type);
	virtual void start() override;
    
    virtual void setUserControl(bool flag) override;
    virtual void attachToLayer(Layer *layer, int zOrder);
    
    virtual void setPosition(const Vec2& pos) override;
    virtual void setAnchorPoint(const Vec2 &anchor) override;
    
    virtual void addEquip(Equip *); // 添加装备
    virtual void removeEquip(Equip *); // 移除装备(对象方式)
    virtual void removeEquipWithIndex(USIZE index); // 移除装备(索引方式)
    virtual void attack(); // 攻击
    virtual void skill(long index); // 施放技能

	void setFaceLeft(bool flag);

    CC_SYNTHESIZE(USIZE, mMp, Mp); // 魔法值
    CC_SYNTHESIZE(USIZE, mEp, Ep); // 怒气值
    CC_SYNTHESIZE(USIZE, mTp, Tp); // 体力值
    CC_SYNTHESIZE(AttackType, mAttackType, AttackType); // 攻击类型
    CC_SYNTHESIZE(Weapon *, mWeapon, Weapon); // 武器
    CC_SYNTHESIZE(Armor *, mArmor, Armor); // 防具
    ADDSETTER(bool, mSkillBusy, setSkillBusy);
   
private:
    void updater(float dt);
    void updateAttack(EffectState state);
	void updateSkill(EffectState state);
    
    EffectState mAttackState = EFFECT_NONE;
    AnimateSprite *mAttackSprite = nullptr;
    
	bool mSkillBusy = false; // 技能施放中
    vector<Skill *> mSkillingList; // 施放中的技能
    vector<long> mEquipments; // 装备列表
    vector<long> mValidSkills; // 已学习技能
};

#endif /* defined(__MyCppGame__Mercenaries__) */
