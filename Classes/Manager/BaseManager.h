//
//  BaseManager.h
//  MyCppGame
//
//  Created by sma11case on 5/12/15.
//
//

#ifndef __MyCppGame__BaseManager__
#define __MyCppGame__BaseManager__

#include "../Common/TypeDefine.h"
#include "cocos2d.h"

class BaseManager
{
public:
	BaseManager(){ allocate(1UL); };
    BaseManager(USIZE capacity){allocate(capacity);};
    ~BaseManager(){delete mPtrBuffer;};
    
	virtual void allocate(USIZE capacity);
    
	virtual void zeroMemory(void **ptr, USIZE size);
    
	virtual void copyMemory(void **dest, void **src, USIZE size);
    
	virtual USIZE add(void *ptr);
    
	virtual void *get(USIZE idx);
    
	virtual bool exists(void *ptr);
    
	virtual void remove(void *ptr);

	virtual void remove(USIZE idx);
    
private:
    USIZE mUsed = 0;
    USIZE mCapacity = 0;
    void **mPtrBuffer = nullptr;
};

#endif /* defined(__MyCppGame__BaseManager__) */
