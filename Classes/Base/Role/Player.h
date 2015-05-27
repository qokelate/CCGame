//
//  Player.h
//  MyCppGame
//
//  Created by sma11case on 5/12/15.
//
//

#ifndef __MyCppGame__Player__
#define __MyCppGame__Player__

#include <stdio.h>
#include "../../Common/Common.h"
#include "Mercenary.h"
#include "../Item/Item.h"

using namespace std;

class Player: Mercenary
{
    virtual void addItem(Equip *); // 添加物品
    virtual void removeItem(Equip *); // 移除物品(对象方式)
    virtual void removeItemWithIndex(USIZE index); // 移除物品(索引方式)
    
private:
    vector<long> items; // 背包
};

#endif /* defined(__MyCppGame__Player__) */
