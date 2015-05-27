//
//  AnimationManager.cpp
//  MyCppGame
//
//  Created by sma11case on 5/12/15.
//
//

#include "AnimationManager.h"

void AnimationManager::addImageCache(char *path, char *key)
{
    Image *img = new Image();
    img->initWithImageFile(path);
    img->autorelease();
	img->retain();
    Director::getInstance()->getTextureCache()->addImage(img, key);
}

Texture2D* AnimationManager::getImageCache(char *key)
{
    Texture2D *cache = Director::getInstance()->getTextureCache()->getTextureForKey(key);
    return cache;
}

void AnimationManager::removeImageCache(char *key)
{
    Director::getInstance()->getTextureCache()->removeTextureForKey(key);
}

Animation* AnimationManager::getAnimationWithCacheSlicing(char *key, USIZE xCount, USIZE yCount)
{
    Texture2D *cache = getImageCache(key);
    
    float w = cache->getContentSizeInPixels().width / xCount;
    float h = cache->getContentSizeInPixels().height / yCount;
    
    auto animation = Animation::create();
    
    for (USIZE a = 0; a < yCount; ++a)
    {
        for (USIZE b = 0; b < xCount; ++b)
        {
            auto frame = SpriteFrame::createWithTexture(cache, Rect(b*w, a*h, w, h));
            animation->addSpriteFrame(frame);
        }
    }
    
    return animation;
}

Animation* AnimationManager::getAnimationWithCacheNamed(char *format, USIZE nStart, USIZE nEnd)
{
    auto cache = SpriteFrameCache::getInstance();
    auto animation = Animation::create();
    
    for (USIZE i = nStart; i <= nEnd; i++)
    {
        auto path = String::createWithFormat(format, i)->getCString();
        auto frame = cache->getSpriteFrameByName(path);
        animation->addSpriteFrame(frame);
    }
    
    return animation;
}

Animation* AnimationManager::getImageAnimationWithPlist(char *plist, char *format, USIZE nStart, USIZE nEnd, char *imagePath)
{
    auto cache = SpriteFrameCache::getInstance();
    
	if (imagePath)
		cache->addSpriteFramesWithFile(plist, imagePath);
    else
        cache->addSpriteFramesWithFile(plist);
    
    auto animation = Animation::create();
    animation->retain();
    
    for (USIZE i = nStart; i <= nEnd; ++i)
    {
        auto path = String::createWithFormat(format, i)->getCString();
        auto frame = cache->getSpriteFrameByName(path);
        animation->addSpriteFrame(frame);
    }
    
    return animation;
}


Animate* AnimationManager::animationToAnimate(Animation *animation, float fps, bool showFirstFrame, USIZE loopCount)
{
    animation->setDelayPerUnit(fps);
	animation->setLoops(loopCount);
    animation->setRestoreOriginalFrame(showFirstFrame);
    auto animate = Animate::create(animation);
    return animate;
}
