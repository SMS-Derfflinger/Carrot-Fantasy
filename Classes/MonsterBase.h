#ifndef __MONSTERBASE_H__
#define __MONSTERBASE_H__

#include "Target.h"

class Monster : public Target {
public:
    // 移动到指定位置
    void moveTo(cocos2d::Vec2 position);
    virtual void moveToSequence(const std::vector<cocos2d::Vec2>& positions);
    // 虚析构
    virtual ~Monster() {};

 

protected:
    int speed;
    Monster() {};// 受保护的构造函数
};

#endif // __MONSTERBASE_H__