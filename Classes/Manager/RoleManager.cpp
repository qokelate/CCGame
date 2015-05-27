//
//  RoleManager.cpp
//  diaoGame
//
//  Created by sma11case on 5/15/15.
//
//

#include "RoleManager.h"
#include "../Base/Role/Role.h"

USIZE RoleManager::add(Role *ptr)
{ 
	ptr->retain();
	return BaseManager::add(ptr);
}

void RoleManager::remove(Role *ptr)
{
	BaseManager::remove(ptr); 
	ptr->release(); 
}

