//
//  GameRoot.cpp
//  GMO
//
//  Created by amos on 15/5/7.
//
//

#include "GameRoot.h"

SceneGame* GameRoot::mSceneGame = NULL;

ConfigManager *gConfigManager = nullptr;

//AnimationManager *gAnimationManager = nullptr;

void GameRoot::InitializeResource()
{
    auto cache = SpriteFrameCache::getInstance();
    cache->addSpriteFramesWithFile("UI.plist", "UI.png");
    cache->addSpriteFramesWithFile("GameBasic.plist", "GameBasic.png");
    cache->addSpriteFramesWithFile("character_res.plist", "character_res.png");
    cache->addSpriteFramesWithFile("smoke.plist", "smoke.png");
    
    char str[64] = {0};
    for (int i = 1; i <= 24; i++)
    {
        sprintf(str, "carrot_die (%d).png", i);
        SpriteFrame* frame = cache->getSpriteFrameByName(str);
        frame->setOffsetInPixels(Vec2(
                                     frame->getOffsetInPixels().x - 40.0f,
                                     frame->getOffsetInPixels().y - 40.0f));
    }
    
    for (int i = 1; i <= 23; i++)
    {
        sprintf(str, "carrot_attack (%d).png", i);
        SpriteFrame* frame = cache->getSpriteFrameByName(str);
        frame->setOffsetInPixels(Vec2(
                                     frame->getOffsetInPixels().x,
                                     frame->getOffsetInPixels().y - 4.0f));
    }
    
    for (int i = 1; i <= 18; i++)
    {
        sprintf(str, "carrot_walk (%d).png", i);
        SpriteFrame* frame = cache->getSpriteFrameByName(str);
        frame->setOffsetInPixels(Vec2(
                                     frame->getOffsetInPixels().x, 
                                     frame->getOffsetInPixels().y - 4.0f));
    }
    
    AnimationManager::addImageCache("res/Skill_5.png", "skill_5");
    
	gConfigManager = new ConfigManager();
}

SceneGame* GameRoot::getSceneGame()
{
    if (mSceneGame == NULL)
        mSceneGame = new SceneGame();
    return mSceneGame;
}

GameRoot::~GameRoot()
{
    delete gConfigManager;
    gConfigManager = nullptr;
}


