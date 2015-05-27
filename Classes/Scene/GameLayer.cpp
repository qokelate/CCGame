#include "GameLayer.h"

GameLayer::GameLayer()
{
	init();

	auto mapLayer = gConfigManager->getMapLayer();
	mapLayer->retain();

    mGameMap = new GameMap();

	Vec2 size = mGameMap->getContentSize();

    mGameMap->setPosition(Vec2(MAP_POS_X, MAP_POS_Y));

	mapLayer->addChild(mGameMap);

	mGameMap = new GameMap();
	mGameMap->setPosition(Vec2(MAP_POS_X+size.x-1.0f, MAP_POS_Y));


    mapLayer->addChild(mGameMap);
    
    schedule(schedule_selector(GameLayer::updateGameLogic));
}

bool GameLayer::init()
{
    Layer::init();
    mPlayer = nullptr;

	return true;
}

GameLayer::~GameLayer()
{
	delete mGameMap;
}

#if 0
void Role::jumpAction(EffectState state)
{
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
}
#endif

void GameLayer::setInDirLRState(InDirState pLeftRightState)
{
	mInDirLRState = pLeftRightState;
}

void GameLayer::setInDirUDState(InDirState pUpDownState)
{
	mInDirUDState = pUpDownState;
}

void GameLayer::setInBtnState(InBtnState pBtnState)
{
	mInBtnState = pBtnState;
}

void GameLayer::setS1BtnState(InBtnState pBtnState)
{
    mS1BtnState = pBtnState;
}

void GameLayer::translateInput()
{
    if (!mPlayer) return;
    
    bool isRun = true;

    switch (mInDirLRState)
    {
        case IN_DIR_LEFT:
            if (isRun) mPlayer->run(DIRECT_RUN_LEFT);
            else mPlayer->walk(DIRECT_WALK_LEFT);
            break;
            
        case IN_DIR_RIGHT:
            if (isRun) mPlayer->run(DIRECT_RUN_RIGHT);
            else mPlayer->walk(DIRECT_WALK_RIGHT);
            break;
            
            case IN_DIR_NO_PRESSED:
            mPlayer->idle();
            break;
    }
    
    switch (mInDirUDState)
    {
        case IN_DIR_UP:
            mPlayer->jump();
            break;
            
        case IN_DIR_DOWN:
            break;
    }
    
    if (IN_BTN_PRESSED == mInBtnState) mPlayer->attack();
    if (IN_BTN_PRESSED == mS1BtnState) mPlayer->skill(0);
}

void GameLayer::updateMoving()
{
    if (!mPlayer) return;
    if (MOVING_NONE == mPlayer->getMovingState()) return;
    
    bool faceLeft = mPlayer->isFaceLeft();
    float x = mPlayer->getMovingScope().x;
    
    float nowX = mPlayer->getPositionX();
    float nowY = mPlayer->getPositionY();
    
    if (faceLeft && nowX <= mMinMovingX)
    {
        Layer *mapLayer = gConfigManager->getMapLayer();
        mapLayer->setPositionX(mapLayer->getPositionX() + x);
        
        Layer *gameLayer = gConfigManager->getGameLayer();
        gameLayer->setPositionX(mapLayer->getPositionX() + x);
        
        mPlayer->setPosition(Vec2(nowX - x, nowY));
        
        mMinMovingX -= x;
        mMaxMovingX -= x;
        return;
    }
    
    if (!faceLeft && nowX >= mMaxMovingX)
    {
        Layer *mapLayer = gConfigManager->getMapLayer();
        mapLayer->setPositionX(mapLayer->getPositionX() - x);
        
        Layer *gameLayer = gConfigManager->getGameLayer();
        gameLayer->setPositionX(mapLayer->getPositionX() - x);
        
        mPlayer->setPosition(Vec2(nowX + x, nowY));
        
        mMinMovingX += x;
        mMaxMovingX += x;
        return;
    }
    
    if (faceLeft) x = -x;
    nowX = nowX + x;
    if (nowX > mMaxMovingX) nowX = mMaxMovingX;
    if (nowX < mMinMovingX) nowX = mMinMovingX;
    mPlayer->setPosition(Vec2(nowX, nowY));
}

void GameLayer::addNPC()
{
    static USIZE b = 0;
    static USIZE a = 0;
    
    a += 1;
//    if (a < 30) return;
    
    a = 0;
    b += 1;
    if (b > 10) return;
    //b = 4;
    
    auto npc = Mercenary::create();
	npc->retain();
    
    auto type = (CCRANDOM_0_1() > 0.5 ? ROLE_WARRIOR : ROLE_NONE);
    npc->initWithType(type);
    if (ROLE_WARRIOR == type) npc->setColor(ccc3(255, 255, 0));

    Vec2 point = Vec2(WIN_WIDTH/4+CCRANDOM_0_1()*200, mGameMap->getWalkableBottom());
    npc->setPosition(point);
 
    npc->attachToLayer(gConfigManager->getGameLayer(), GAME_PLAYER_LAYER_LEVEL);
	npc->start();
    
    if (CCRANDOM_0_1() > 0.5) npc->setFaceLeft(true);
    
	gConfigManager->getRoleManager()->add(npc);
    
    if (b == 1)
    {
        Role *temp = (Role *)gConfigManager->getRoleManager()->get(0);
        gConfigManager->setUnderControl(temp);
        mPlayer = (Mercenary *)gConfigManager->getUnderControl();
		mPlayer->setRunSpeed(10.0f);
		mPlayer->setWalkSpeed(5.0f);
    }
    
    return;
}

void GameLayer::updateGameLogic(float dt)
{
    addNPC();
    translateInput();
    updateMoving();
}

