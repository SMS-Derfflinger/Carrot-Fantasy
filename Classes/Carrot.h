#ifndef __CARROT_H__
#define __CARROT_H__

// 导入头文件
#include "cocos2d.h"

USING_NS_CC;

// 创建一个萝卜类
class Carrot : public cocos2d::Sprite
{
private:
    // 血量
    int HP;
    cocos2d::Vec2 position;
public:
    void takeDamage(int damage);
    // 初始化函数
    void setCarrotPosition(cocos2d::Vec2 pos);
    cocos2d::Vec2 getCarrotPosition() const;
    virtual bool init() override;
    CREATE_FUNC(Carrot);
};

#endif // __CARROT_H__