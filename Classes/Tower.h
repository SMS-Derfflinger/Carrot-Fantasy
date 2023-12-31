#ifndef __TOWER_H__
#define __TOWER_H__

#include "TowerBase.h"

class BottleTower_1 : public BottleTower {
public:
    // 初始化函数
    virtual bool init() override;
    CREATE_FUNC(BottleTower_1);
};

class BottleTower_2 : public BottleTower {
public:
    // 初始化函数
    virtual bool init() override;
    CREATE_FUNC(BottleTower_2);
};

class BottleTower_3 : public BottleTower {
public:
    // 初始化函数
    virtual bool init() override;
    CREATE_FUNC(BottleTower_3);
};

class SunflowerTower_1 : public SunflowerTower {
public:
    // 初始化函数
    bool init() override;
    CREATE_FUNC(SunflowerTower_1);
};

class SunflowerTower_2 : public SunflowerTower {
public:
    // 初始化函数
    bool init() override;
    CREATE_FUNC(SunflowerTower_2);
};

class SunflowerTower_3 : public SunflowerTower {
public:
    // 初始化函数
    bool init() override;
    CREATE_FUNC(SunflowerTower_3);
};

class StarTower_1 : public StarTower {
public:
    // 初始化函数
    bool init() override;
    CREATE_FUNC(StarTower_1);
};

class StarTower_2 : public StarTower {
public:
    // 初始化函数
    bool init() override;
    CREATE_FUNC(StarTower_2);
};

class StarTower_3 : public StarTower {
public:
    // 初始化函数
    bool init() override;
    CREATE_FUNC(StarTower_3);
};

#endif // __TOWER_H__