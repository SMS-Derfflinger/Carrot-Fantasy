#include "Obstacle.h"

bool TestObstacle::init() {
    if (!Sprite::init()) {
        return false;
    }


    // 初始化障碍物的外观和属性
    this->initWithFile("CloseNormal.png");
    // 初始化HP，价值和半径
    maxHP = HP = 100;
    value = 50;
    radius = 50;

    return true;
}