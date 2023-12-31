#ifndef __TARGET_H__
#define __TARGET_H__

#include "cocos2d.h"
#include "ui/CocosGUI.h"

class Target : public cocos2d::Sprite {
public:
    // 虚析构
    virtual ~Target() {};
    // 受伤
    virtual void takeDamage(int damage);
    // 判断是否存活
    bool isAlive() const;
    // 设置血量
    void setHP(int HP);
    // 获取半径
    int getRadius();
    void setAllTarget();


protected:
    int HP;  // 血量
    int maxHP; // 最大血量
    int value;// 击杀奖励
    int radius;// 半径
    cocos2d::ProgressTimer* Progress = nullptr;// 保存进度条的指针
    Target() {};// 受保护的构造函数
};

#endif // __TARGET_H__