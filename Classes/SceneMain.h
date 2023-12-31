#ifndef __SCENCEMAIN_SCENE_H__
#define __SCENCEMAIN_SCENE_H__

#include "SceneBase.h"

class SceneBase;
class Scene1 : public SceneBase
{
public:
    static Scene1* createScene(int level, LevelScene* levelScene);
    virtual bool init(int level, LevelScene* levelScene) override;
    virtual void initMonster(int choose) override;
    virtual ~Scene1() {};
};

class Scene2 : public SceneBase
{
public:
    static Scene2* createScene(int level, LevelScene* levelScene);
    virtual bool init(int level, LevelScene* levelScene) override;
    virtual void initMonster(int choose) override;
    // 虚析构
    virtual ~Scene2() {};
};

class Scene3 : public SceneBase
{
public:
    static Scene3* createScene(int level, LevelScene* levelScene);
    virtual bool init(int level, LevelScene* levelScene) override;
    virtual void initMonster(int choose) override;
    void initMonsterPlace2();                       //第二个怪物出生点
    // 虚析构
    virtual ~Scene3() {};
protected:
    std::vector<cocos2d::Vec2> path1;                //另一条移动路径
};
#endif // __SCENCEMAIN_SCENE_H__