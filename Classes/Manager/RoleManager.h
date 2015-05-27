//
//  RoleManager.h
//  diaoGame
//
//  Created by sma11case on 5/15/15.
//
//

#ifndef __diaoGame__RoleManager__
#define __diaoGame__RoleManager__

#include <stdio.h>
#include "../Common/Common.h"
#include "BaseManager.h"

class Role;

class RoleManager : public BaseManager
{
public:
	RoleManager(USIZE capacity) :BaseManager(capacity){};
	virtual USIZE add(Role *ptr);
	virtual void remove(Role *ptr);
};

#endif /* defined(__diaoGame__RoleManager__) */
