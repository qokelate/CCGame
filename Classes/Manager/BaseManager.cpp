//
//  BaseManager.cpp
//  MyCppGame
//
//  Created by sma11case on 5/12/15.
//
//

#include "BaseManager.h"

void BaseManager::allocate(USIZE capacity)
{
	CCASSERT(capacity, "capacity must > 0");
	if (mPtrBuffer) delete mPtrBuffer;
	mPtrBuffer = new void*[capacity];
	mCapacity = capacity;
	mUsed = 0UL;
}

void BaseManager::zeroMemory(void **ptr, USIZE size)
{
	for (USIZE idx = 0; idx < size; ++idx)
	{
		ptr[idx] = nullptr;
	}
}

void BaseManager::copyMemory(void **dest, void **src, USIZE size)
{
	for (USIZE idx = 0; idx < size; ++idx)
	{
		dest[idx] = src[idx];
	}
}

USIZE BaseManager::add(void *ptr)
{
	CCASSERT(mCapacity, "capacity must > 0");
	if (mUsed == mCapacity)
	{
		auto newSize = mCapacity * 2;
		auto buffer = new void*[newSize];
		copyMemory(buffer, mPtrBuffer, mUsed);

		delete mPtrBuffer;
		mCapacity = newSize;
		mPtrBuffer = buffer;
	}

	mPtrBuffer[mUsed] = ptr;
	auto idx = mUsed++;

	return idx;
}

void *BaseManager::get(USIZE idx)
{ 
	return mPtrBuffer[idx];
}

bool BaseManager::exists(void *ptr)
{
	for (USIZE idx = 0; idx < mUsed; ++idx)
	{
		if (mPtrBuffer[idx] == ptr) return true;
	}
	return false;
}

void BaseManager::remove(void *ptr)
{
	for (USIZE idx = 0; idx < mUsed; ++idx)
	{
		if (mPtrBuffer[idx] != ptr) continue;
		mPtrBuffer[idx] = mPtrBuffer[--mUsed];
		break;
	}
}

void BaseManager::remove(USIZE idx)
{
	mPtrBuffer[idx] = mPtrBuffer[--mUsed];
}

