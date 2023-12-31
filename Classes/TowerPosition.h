#ifndef __YOUR_GAME_SCENE_H__
#define __YOUR_GAME_SCENE_H__

#include "tower.h"
#include "cocos2d.h"

// 创建一个炮塔对象类
class TowerPosition : public cocos2d::Sprite
{
public:
    CREATE_FUNC(TowerPosition);
    // 虚析构
    virtual ~TowerPosition() {};
    // 初始化函数
    virtual bool init() override;
    Tower* towerofThisPosition;
};

#endif // __YOUR_GAME_SCENE_H__