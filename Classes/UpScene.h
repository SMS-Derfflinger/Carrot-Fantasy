#ifndef __UP_SCENE_H__
#define __UP_SCENE_H__

#include "cocos2d.h"

class LevelScene;

class UpScene : public cocos2d::Scene
{
public:
    static UpScene* create(LevelScene* levelScene);
    cocos2d::Label* m_upgrade1Label;
    cocos2d::Label* m_upgrade2Label;
    virtual bool init(LevelScene* levelScene);
    void onItem1Button(Ref* sender);
    void onItem2Button(Ref* sender);
    cocos2d::Label* m_item1LevelLabel;
    cocos2d::Label* m_item2LevelLabel;
private:
    void onBackButton(cocos2d::Ref* sender);

    LevelScene* m_levelScene;
    cocos2d::Label* m_moneyLabel;
};

#endif // __UP_SCENE_H__