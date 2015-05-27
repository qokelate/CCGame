#ifndef _GAME_LAYER_H_
#define _GAME_LAYER_H_

#include "GameMap.h"
#include "../Common/Common.h"

#include "../Base/Role/Mercenary.h"
#include "../Manager/AnimationManager.h"
#include "../Base/Role/Role.h"
#include "../Manager/RoleManager.h"

using std::list;

class GameLayer : public Layer
{
public :
	GameLayer();
	~GameLayer();
    bool init();

	void setInDirLRState(InDirState pLeftRightState);	//Left or Right
	void setInDirUDState(InDirState pUpDownState);	//Up or Down
	void setInBtnState(InBtnState pBtnState); // attack
    void setS1BtnState(InBtnState pBtnState); // skill
    
private :
	GameMap* mGameMap = nullptr;
    Mercenary *mPlayer = nullptr;
    float mMinMovingX = VALID_MIN_MAP_X;
    float mMaxMovingX = VALID_MAX_MAP_X;
    
	InDirState mInDirLRState = IN_DIR_NO_PRESSED;
	InDirState mInDirUDState = IN_DIR_NO_PRESSED;
	InBtnState mInBtnState = IN_BTN_NO_PRESSED;
    InBtnState mS1BtnState = IN_BTN_NO_PRESSED;

    void addNPC();
    
    void updateGameLogic(float dt);
    void translateInput();
    void updateMoving();
};

#endif