#pragma once
#include "Material.h"

/*-----------------------------------------------------------------------
 * 类名: CManor
 * 说明: 庄园类, 用来进入庄园, 因为要采集物品, 所以集成 CMaterial 材料类
-----------------------------------------------------------------------*/
class CManor 
    : public CMaterial {
public:

    void intoMyManor(); // 进入我的庄园
    void leaveManor(); // 离开庄园
    void UpgradeMushroom(); // 升级育菇木床
};

