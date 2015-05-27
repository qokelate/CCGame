#ifndef _HUD_LAYER_H_
#define _HUD_LAYER_H_

#include "cocos2d.h"
USING_NS_CC;

#include "../Common/Common.h"

#include "../Sneaky/SneakyButton.h"
#include "../Sneaky/SneakyButtonSkinnedBase.h"
#include "../Sneaky/SneakyJoystick.h"
#include "../Sneaky/SneakyJoystickSkinnedBase.h"

class HudLayer : public Layer
{
public :
	HudLayer();
	bool init();
	~HudLayer();

	InDirState getInDirLRState();	//Left or Right
	InDirState getInDirUDState();	//Up or Down
	InBtnState getInBtnState();
    InBtnState getS1BtnState();

private :
    SneakyButton* mSkill_1;
	SneakyButton* mButtonA;
	SneakyJoystick* mJoystick;
	void menuPauseCallback(Ref* pSender);
};

#endif