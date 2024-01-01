#ifndef __LEVEL_SCENE_H__
#define __LEVEL_SCENE_H__
#include "cocos2d.h"
class GameScene; // 声明 GameScene 类
class LevelScene : public cocos2d::Scene
{
public:
    static LevelScene* create();
    void unlockLevel(int level);
    virtual bool init();
    bool m_unlockedLevels[3];
    int m_unlockedLevel1;
    int m_unlockedLevel2 ;
    int m_unlockedLevel3 ;
    void selectLevel1(cocos2d::Ref* sender);
    void selectLevel2(cocos2d::Ref* sender);
    void selectLevel3(cocos2d::Ref* sender);
    int m_unlockLevel ;// 保存已解锁的关卡编号
    cocos2d::MenuItemImage* m_level1Button;
    cocos2d::MenuItemImage* m_level2Button;
    cocos2d::MenuItemImage* m_level3Button;
    void updateButtonState();
    cocos2d::Sprite* m_gameImage; // mubu
    int money;//局外货币
    cocos2d::Label* m_moneyLabel;//显示钱
    void consumeMoney(int n);//花钱
    int getMoney();//返回钱
    void enterUpgradeScene(cocos2d::Ref* sender);
    int skill1 = 0;//技能等级
    //int skill2 = 0;
    void upgradeItem1();//获取技能等级与返回
    //void upgradeItem2();
    int getItem1Level();
    //int getItem2Level();
private:
    
    cocos2d::Scene* m_gameScene; // 保存 GameScene 场景的指针
};

#endif // __LEVEL_SCENE_H__