#include "HudLayer.h"

const float PAUSE_MENU_POS_X = 460;
const float PAUSE_MENU_POS_Y = 300;

const float JOYSTICK_POS_X = 50;
const float JOYSTICK_POS_Y = 50;
const float JOYSTICK_DEAD_RADIUS = 10;
const float JOYSTICK_THRESHOLD = 0.4f;

const float BTN_A_POS_X = 430;
const float BTN_A_POS_Y = 50;

HudLayer::HudLayer()
{
	auto btn_pause = MenuItemSprite::create(
		Sprite::createWithSpriteFrameName("CloseNormal.png"),
		Sprite::createWithSpriteFrameName("CloseSelected.png"), CC_CALLBACK_1(HudLayer::menuPauseCallback, this));
    btn_pause->setPosition(Point::ZERO);
	auto menu_pause = Menu::createWithItem(btn_pause);
	menu_pause->setPosition(Vec2(PAUSE_MENU_POS_X, PAUSE_MENU_POS_Y));
	this->addChild(menu_pause);

	mJoystick = new SneakyJoystick();
    mJoystick->initWithRect(Rect::ZERO);
	mJoystick->setAutoCenter(true);
	mJoystick->setHasDeadzone(true);
	mJoystick->setDeadRadius(JOYSTICK_DEAD_RADIUS);
	auto jstickSkin = new SneakyJoystickSkinnedBase();
	jstickSkin->autorelease();
	jstickSkin->init();
	jstickSkin->setBackgroundSprite(Sprite::createWithSpriteFrameName("JoyStick-base.png"));
	jstickSkin->setThumbSprite(Sprite::createWithSpriteFrameName("JoyStick-thumb.png"));
	//jstickSkin->getThumbSprite()->setScale(0.5f);
	jstickSkin->setPosition(Vec2(JOYSTICK_POS_X, JOYSTICK_POS_Y));
	jstickSkin->setJoystick(mJoystick);
	this->addChild(jstickSkin);

	mButtonA = new SneakyButton();
    mButtonA->initWithRect(Rect::ZERO);
	mButtonA->setIsToggleable(false);
	mButtonA->setIsHoldable(true);
	auto btnASkin = new SneakyButtonSkinnedBase();
	btnASkin->autorelease();
	btnASkin->init();
	btnASkin->setPosition(Vec2(BTN_A_POS_X, BTN_A_POS_Y));
	btnASkin->setDefaultSprite(Sprite::createWithSpriteFrameName("button-default.png"));
	btnASkin->setPressSprite(Sprite::createWithSpriteFrameName("button-pressed.png"));
	btnASkin->setActivatedSprite(Sprite::createWithSpriteFrameName("button-activated.png"));
	//btnASkin->setDisabledSprite(CCSprite::createWithSpriteFrameName("button-disabled.png"));
	btnASkin->setButton(mButtonA);
	this->addChild(btnASkin);
    
    
    

    
    {
        mSkill_1 = new SneakyButton();
        mSkill_1->initWithRect(Rect::ZERO);
        mSkill_1->setIsToggleable(false);
        mSkill_1->setIsHoldable(true);
        auto btnASkin = new SneakyButtonSkinnedBase();
        btnASkin->autorelease();
        btnASkin->init();
        btnASkin->setPosition(Vec2(BTN_A_POS_X-100, BTN_A_POS_Y));
        btnASkin->setDefaultSprite(Sprite::createWithSpriteFrameName("button-default.png"));
        btnASkin->setPressSprite(Sprite::createWithSpriteFrameName("button-pressed.png"));
        btnASkin->setActivatedSprite(Sprite::createWithSpriteFrameName("button-activated.png"));
        //btnASkin->setDisabledSprite(CCSprite::createWithSpriteFrameName("button-disabled.png"));
        btnASkin->setButton(mSkill_1);
        this->addChild(btnASkin);
    }
    

	init();
}

bool HudLayer::init()
{
	//CCLayer::init();
	return true;
}

HudLayer::~HudLayer()
{
	delete mButtonA;
	delete mJoystick;
}

InDirState HudLayer::getInDirLRState()
{
	bool left, right;
	Point velocity = mJoystick->getVelocity();

	left = (velocity.x <= -JOYSTICK_THRESHOLD ? true : false);
	right = (velocity.x >= JOYSTICK_THRESHOLD ? true : false);

	InDirState retState = IN_DIR_NO_PRESSED;
	if (left)
		retState = IN_DIR_LEFT;
	else if (right)
		retState = IN_DIR_RIGHT;
	else
		retState = IN_DIR_NO_PRESSED;

	return retState;
}

InDirState HudLayer::getInDirUDState()
{
	bool up, down;
	Point velocity = mJoystick->getVelocity();

	up = (velocity.y >= JOYSTICK_THRESHOLD ? true : false);
	down = (velocity.y <= -JOYSTICK_THRESHOLD ? true : false);

	InDirState retState = IN_DIR_NO_PRESSED;
	if (up)
		retState = IN_DIR_UP;
	else if (down)
		retState = IN_DIR_DOWN;
	else
		retState = IN_DIR_NO_PRESSED;

	return retState;

}

InBtnState HudLayer::getInBtnState()
{
	InBtnState retState = IN_BTN_NO_PRESSED;

	if (mButtonA->getIsActive())
		retState = IN_BTN_PRESSED;

	return retState;
}

InBtnState HudLayer::getS1BtnState()
{
    InBtnState retState = IN_BTN_NO_PRESSED;
    
    if (mSkill_1->getIsActive())
        retState = IN_BTN_PRESSED;
    
    return retState;
}

void HudLayer::menuPauseCallback(Ref* pSender)
{
    CONLOG("不要乱点!!!");
}
