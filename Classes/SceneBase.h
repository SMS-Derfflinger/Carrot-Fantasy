#ifndef __SCENCEBASE_SCENE_H__
#define __SCENCEBASE_SCENE_H__

#include "LevelScene.h"
#include "cocos2d.h"
#include "Target.h"

USING_NS_CC; //using namespace cocos2d

class SceneBase : public cocos2d::Scene
{
public:
    static SceneBase* createScene(int level, LevelScene* levelScene);

    // 虚析构
    virtual ~SceneBase() {};

    virtual bool init(int level, LevelScene* levelScene);

    virtual void initMonster(int choose) {};    //初始化怪物，choose选择初始化哪种怪物

    void takeCarrotDamage(int damage);

    void setButton(bool flag);   // 游戏完成时调用的放置按钮函数，为true获胜，为false失败

    cocos2d::Vec2 getCarrotPosition() const;

    void setCarrotPosition(cocos2d::Vec2 position);

    void initScene(std::string& mapname);   
    
    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);

    void createBottle(cocos2d::Ref* sender);     //放置瓶子炮塔

    void createStar(cocos2d::Ref* sender);       //放置星星炮塔

    void createSunflower(cocos2d::Ref* sender);  //放置太阳花炮塔

    void onGameWin();

    void onGameFail();

    void update(float delta);

    void addMoney(int money);

    void updateMoney(int money);

    void updateBottle1(cocos2d::Ref* sender);

    /*void updateBottle2(cocos2d::Ref* sender);

    void removeBottle(cocos2d::Ref* sender);

    void updateStar1(cocos2d::Ref* sender);

    void updateStar2(cocos2d::Ref* sender);

    void removeStar(cocos2d::Ref* sender);

    void updateSunflower1(cocos2d::Ref* sender);

    void updateSunflower1(cocos2d::Ref* sender);

    void removeSunflower(cocos2d::Ref* sender);*/

protected:
    cocos2d::Label* m_lable;            //显示当前金钱
    bool monsterFlag = false;           //怪物是否生成完毕的标志，true为生成完毕
    float time = 0.0f;                  //游戏的持续时间
    Sprite* m_carrot;                   //指向萝卜的指针
    int moneyScene;                     //场景中的的钱
    int carrotHP = 10;                  //萝卜的初始血量
    cocos2d::Vec2 carrotPosition;       //萝卜的位置
    std::vector<cocos2d::Vec2> path;    //移动路径
    int m_level;                        //保存当前的关卡编号
    LevelScene* m_levelScene;           //保存关卡选择场景的指针
};

#endif  //__SCENCEBASE_SCENE_H__

