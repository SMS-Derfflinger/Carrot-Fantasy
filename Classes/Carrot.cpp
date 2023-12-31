#include "Carrot.h"

bool Carrot::init()
{
    if (!Sprite::init())
    {
        return false;
    }

    // 初始化障碍物的外观和属性
    this->initWithFile("luobo.png");

    // 初始化HP
    HP = 10;

    return true;
}

void Carrot::takeDamage(int damage)
{
    if (HP > damage)
        HP -= damage;
    else
        HP = 0;
}

void Carrot::setCarrotPosition(cocos2d::Vec2 pos)
{
    this->position = pos;
}

Vec2 Carrot::getCarrotPosition() const
{
    return position;
}


