// TowerPosition.cpp
#include "TowerPosition.h"

USING_NS_CC;

bool TowerPosition::init()
{
    if (!Sprite::init())
    {
        return false;
    }
    // 初始化炮塔的外观和属性
    this->initWithFile("addTower.png");
    towerofThisPosition = nullptr;

    return true;
}

