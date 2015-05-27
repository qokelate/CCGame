//
//  CommonConfig.cpp
//  MyCppGame
//
//  Created by sma11case on 5/13/15.
//
//

#include "ConfigManager.h"
#include "../Base/Role/Role.h"

void ConfigManager::setUnderControl(Role* obj)
{
    if (mUnderControl) mUnderControl->setUserControl(false);
    mUnderControl = obj;
	if (mUnderControl)
	{
		mUnderControl->setUserControl(true);
		mUnderControl->setCampType(CAMP_PLAYER);
	}
}




