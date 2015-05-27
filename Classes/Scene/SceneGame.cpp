//
//  SceneGame.cpp
//  GMO
//
//  Created by amos on 15/5/7.
//
//

#include "SceneGame.h"

SceneGame::SceneGame()
{
	init();
}

bool SceneGame::init()
{
    Scene::init();

	Layer *mapLayer = Layer::create();
	mapLayer->setPosition(Vec2(0, 0));
	mapLayer->retain();
	gConfigManager->setMapLayer(mapLayer);

	mHudLayer = new HudLayer();
	mHudLayer->setPosition(Vec2(0, 0));
	mHudLayer->retain();
	gConfigManager->setHudLayer(mHudLayer);

	mGameLayer = new GameLayer();
	mGameLayer->setPosition(Vec2(0, 0));
	mGameLayer->retain();
	gConfigManager->setGameLayer(mGameLayer);

	RoleManager *rm = new RoleManager(CONFIG_ROLEMANAGER_SIZE);
	gConfigManager->setRoleManager(rm);

	addChild(mapLayer, GAME_MAP_LAYER_LEVEL);
	addChild(mGameLayer, GAME_PLAYER_LAYER_LEVEL);
	addChild(mHudLayer, GAME_HUD_LAYER_LEVEL);

	gConfigManager->setMissionScene(this);
	this->schedule(schedule_selector(SceneGame::broadcastInput));
    
    BufferManager *bm = new BufferManager();
    gConfigManager->setBufferManager(bm);

	auto bge = SimpleAudioEngine::sharedEngine();
	bge->playBackgroundMusic("res/Music/bg.mp3", true);
    //bge->playBackgroundMusic("res/sound/music_boss2.mp3", true);
    bge->setBackgroundMusicVolume(0.1f);
    bge->setEffectsVolume(1.0f);
    
    CONLOG("ptr=%p DebugMode=%d", this, GAME_DEBUG_MODE);

    return true;
}

SceneGame::~SceneGame()
{
	delete gConfigManager->getRoleManager();
    delete gConfigManager->getBufferManager();
    delete mHudLayer;
    delete mGameLayer;

	gConfigManager->setRoleManager(nullptr);
	gConfigManager->setBufferManager(nullptr);
}

void SceneGame::broadcastInput(float dt)
{
    mGameLayer->setInDirLRState(mHudLayer->getInDirLRState());
    mGameLayer->setInDirUDState(mHudLayer->getInDirUDState());
    mGameLayer->setInBtnState(mHudLayer->getInBtnState());
    mGameLayer->setS1BtnState(mHudLayer->getS1BtnState());
}
