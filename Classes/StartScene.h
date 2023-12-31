#ifndef __START_SCENE_H__
#define __START_SCENE_H__
#include "cocos2d.h"

class StartScene : public cocos2d::Scene
{
public:
    static StartScene* create();

    virtual bool init() override;
    void startGame(cocos2d::Ref* sender);
};

#endif // __START_SCENE_H__
