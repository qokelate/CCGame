//
//  AnimationManager.h
//  MyCppGame
//
//  Created by sma11case on 5/12/15.
//
//

#ifndef __MyCppGame__AnimationManager__
#define __MyCppGame__AnimationManager__

#include <stdio.h>
#include "../Common/TypeDefine.h"
#include "../Common/DebugHelper.h"
#include "BaseManager.h"
#include "cocos2d.h"

using namespace cocos2d;

class AnimationManager
{
public:
	ALLOCATE(AnimationManager, "AnimationManager");
	RELEASE(AnimationManager, "AnimationManager");
    static void addImageCache(char *path, char *key);
    static Texture2D *getImageCache(char *key);
    static void removeImageCache(char *key);

	static Animation* getAnimationWithCacheSlicing(char *key, USIZE xCount, USIZE yCount);
	static Animation* getAnimationWithCacheNamed(char *format, USIZE nStart, USIZE nEnd);
	static Animation* getImageAnimationWithPlist(char *plist, char *format, USIZE nStart, USIZE nEnd, char *imagePath);
	static Animate* animationToAnimate(Animation *animation, float fps, bool showFirstFrame, USIZE loopCount);
};

#endif /* defined(__MyCppGame__AnimationManager__) */
