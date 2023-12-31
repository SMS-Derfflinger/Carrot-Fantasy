#include "SceneBase.h"
#include "SceneMain.h"
#include "Obstacle.h"
#include "Monster.h"
#include "Tower.h"
#include "Carrot.h"
#include "TowerPosition.h"
#include "ui/CocosGUI.h"

USING_NS_CC; //using namespace cocos2d

Scene1* Scene1::createScene(int level, LevelScene* levelScene)
{
    Scene1* scene = new Scene1();
    if (scene && scene->init(level, levelScene))
    {
        scene->autorelease();
        return scene;
    }
    else
    {
        delete scene;
        return nullptr;
    }
    return scene;
}

// 打印有用的错误消息，而不是在文件不存在时段错误。
static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

//1为普通兔子，2为滑板兔，3为飞行兔
void Scene1::initMonster(int choose)
{
    if (choose == 1)
    {
        Rabbit* Monster = Rabbit::create();
        Monster->setPosition(Vec2(300 + 50, 500 + 50));
        this->addChild(Monster);
        Monster->moveToSequence(path);
    }
    else if (choose == 2)
    {
        FastrRabbit* Monster = FastrRabbit::create();
        Monster->setPosition(Vec2(300 + 50, 500 + 50));
        this->addChild(Monster);
        Monster->moveToSequence(path);
    }
    else if (choose == 3)
    {
        FlyingRabbit* Monster = FlyingRabbit::create();
        Monster->setPosition(Vec2(300 + 50, 500 + 50));
        this->addChild(Monster);
        Monster->moveToSequence(path);
    }
}

// on "init" you need to initialize your instance
bool Scene1::init(int level, LevelScene* levelScene)
{
    // 调用了父类Scene的init()函数进行初始化，如果初始化失败，则返回false
    if (!SceneBase::init(level, levelScene))
    {
        return false;
    }

    moneyScene = 500;
    m_level = level;
    m_levelScene = levelScene; // 保存关卡选择场景的指针

    std::string mapName = "Level 1.tmx";
    initScene(mapName);

    // 创建 Label，并设置字体、字号和初始文本内容
    int number = moneyScene; // 要显示的数字
    std::string text = std::to_string(number); // 将数字转换为字符串
    m_lable = Label::createWithTTF(text, "fonts/arial.ttf", 48);
    m_lable->setPosition(Vec2(260, 763));
    this->addChild(m_lable, 1);

    path = {
        cocos2d::Vec2(300 + 50, 100 + 50),
        cocos2d::Vec2(900 + 50, 100 + 50),
        cocos2d::Vec2(900 + 50, 500 + 50),
        cocos2d::Vec2(550 + 50, 500 + 50),
    };

    Sprite* gameProgress = Sprite::create("Rabbit.png");    //创建进度条
    gameProgress->setPosition(Vec2(420, 765));
    gameProgress->runAction(cocos2d::MoveBy::create(50, Vec2(400, 0)));
    this->addChild(gameProgress, 4);
    auto createRabbit = CallFunc::create([=]() {initMonster(1); });
    auto createFastr = CallFunc::create([=]() {initMonster(2); });
    auto createFlying = CallFunc::create([=]() {initMonster(3); });

    runAction(Sequence::create(
        DelayTime::create(2), createRabbit,
        DelayTime::create(2), createFastr,
        DelayTime::create(2), createRabbit,
        DelayTime::create(2), createRabbit,

        DelayTime::create(12), createFlying,
        DelayTime::create(2), createRabbit,
        DelayTime::create(2), createFlying,
        DelayTime::create(2), createRabbit,
        DelayTime::create(2), createRabbit,

        DelayTime::create(12), createRabbit,
        DelayTime::create(2), createRabbit,
        DelayTime::create(2), createFlying,
        DelayTime::create(2), createRabbit,
        DelayTime::create(2), createFlying,
        DelayTime::create(1), createRabbit,

        CallFunc::create([=]() {monsterFlag=true; }),
        nullptr));

    return true;
}

Scene2* Scene2::createScene(int level, LevelScene* levelScene)
{
    Scene2* scene = new Scene2();
    if (scene && scene->init(level, levelScene))
    {
        scene->autorelease();
        return scene;
    }
    else
    {
        delete scene;
        return nullptr;
    }
    return scene;
}

void Scene2::initMonster(int choose)
{
    if (choose == 1)
    {
        Rabbit* Monster = Rabbit::create();
        Monster->setPosition(Vec2(200 + 50, 500 + 50));
        this->addChild(Monster);
        Monster->moveToSequence(path);
    }
    else if (choose == 2)
    {
        FastrRabbit* Monster = FastrRabbit::create();
        Monster->setPosition(Vec2(200 + 50, 500 + 50));
        this->addChild(Monster);
        Monster->moveToSequence(path);
    }
    else if (choose == 3)
    {
        FlyingRabbit* Monster = FlyingRabbit::create();
        Monster->setPosition(Vec2(200 + 50, 500 + 50));
        this->addChild(Monster);
        Monster->moveToSequence(path);
    }
}

// on "init" you need to initialize your instance
bool Scene2::init(int level, LevelScene* levelScene)
{
    // 调用了父类Scene的init()函数进行初始化，如果初始化失败，则返回false
    if (!SceneBase::init(level, levelScene))
    {
        return false;
    }

    moneyScene = 700;
    m_level = level;
    m_levelScene = levelScene; // 保存关卡选择场景的指针

    std::string mapName = "Level 2.tmx";
    initScene(mapName);

    // 创建 Label，并设置字体、字号和初始文本内容
    int number = moneyScene; // 要显示的数字
    std::string text = std::to_string(number); // 将数字转换为字符串
    m_lable = Label::createWithTTF(text, "fonts/arial.ttf", 48);
    m_lable->setPosition(Vec2(260, 763));
    this->addChild(m_lable, 1);

    path = {
    cocos2d::Vec2(200 + 50, 100 + 50),
    cocos2d::Vec2(400 + 50, 100 + 50),
    cocos2d::Vec2(400 + 50, 300 + 50),
    cocos2d::Vec2(300 + 50, 300 + 50),
    cocos2d::Vec2(300 + 50, 500 + 50),
    cocos2d::Vec2(500 + 50, 500 + 50),
    cocos2d::Vec2(500 + 50, 100 + 50),
    cocos2d::Vec2(700 + 50, 100 + 50),
    cocos2d::Vec2(700 + 50, 300 + 50),
    cocos2d::Vec2(950 + 50, 300 + 50)
    };

    Sprite* gameProgress = Sprite::create("Rabbit.png");    //创建进度条
    gameProgress->setPosition(Vec2(420, 765));
    gameProgress->runAction(cocos2d::MoveBy::create(70, Vec2(400, 0)));
    this->addChild(gameProgress, 4);

    auto createRabbit = CallFunc::create([=]() {initMonster(1); });
    auto createFastr = CallFunc::create([=]() {initMonster(2); });
    auto createFlying = CallFunc::create([=]() {initMonster(3); });
    runAction(Sequence::create(
        DelayTime::create(2), createRabbit,
        DelayTime::create(2), createFastr,
        DelayTime::create(2), createRabbit,
        DelayTime::create(2), createRabbit,

        DelayTime::create(12), createFlying,
        DelayTime::create(2), createRabbit,
        DelayTime::create(2), createFlying,
        DelayTime::create(2), createRabbit,
        DelayTime::create(2), createRabbit,

        DelayTime::create(12), createRabbit,
        DelayTime::create(2), createRabbit,
        DelayTime::create(2), createFlying,
        DelayTime::create(2), createRabbit,
        DelayTime::create(2), createFlying,

        DelayTime::create(12), createRabbit,
        DelayTime::create(2), createRabbit,
        DelayTime::create(2), createFlying,
        DelayTime::create(2), createFastr, 
        DelayTime::create(2), createFlying,
        DelayTime::create(1), createRabbit,
        CallFunc::create([=]() {monsterFlag = true; }),
        nullptr));

    return true;
}

Scene3* Scene3::createScene(int level, LevelScene* levelScene)
{
    Scene3* scene = new Scene3();
    if (scene && scene->init(level, levelScene))
    {
        scene->autorelease();
        return scene;
    }
    else
    {
        delete scene;
        return nullptr;
    }
    return scene;
}

void Scene3::initMonster(int choose)    //1-3在上方出生点，4-6在下方出生点
{
    if (choose == 1)
    {
        Rabbit* Monster = Rabbit::create();
        Monster->setPosition(Vec2(100 + 50, 500 + 50));
        this->addChild(Monster);
        Monster->moveToSequence(path);
    }
    else if (choose == 2)
    {
        FastrRabbit* Monster = FastrRabbit::create();
        Monster->setPosition(Vec2(100 + 50, 500 + 50));
        this->addChild(Monster);
        Monster->moveToSequence(path);
    }
    else if (choose == 3)
    {
        FlyingRabbit* Monster = FlyingRabbit::create();
        Monster->setPosition(Vec2(100 + 50, 500 + 50));
        this->addChild(Monster);
        Monster->moveToSequence(path);
    }
    if (choose == 4)
    {
        Rabbit* Monster = Rabbit::create();
        Monster->setPosition(Vec2(100 + 50, 100 + 50));
        this->addChild(Monster);
        Monster->moveToSequence(path1);
    }
    else if (choose == 5)
    {
        FastrRabbit* Monster = FastrRabbit::create();
        Monster->setPosition(Vec2(100 + 50, 100 + 50));
        this->addChild(Monster);
        Monster->moveToSequence(path1);
    }
    else if (choose == 6)
    {
        FlyingRabbit* Monster = FlyingRabbit::create();
        Monster->setPosition(Vec2(100 + 50, 100 + 50));
        this->addChild(Monster);
        Monster->moveToSequence(path1);
    }
}

// on "init" you need to initialize your instance
bool Scene3::init(int level, LevelScene* levelScene)
{
    // 调用了父类Scene的init()函数进行初始化，如果初始化失败，则返回false
    if (!SceneBase::init(level, levelScene))
    {
        return false;
    }

    moneyScene = 1000;
    m_level = level;
    m_levelScene = levelScene; // 保存关卡选择场景的指针

    std::string mapName = "Level 3.tmx";
    initScene(mapName);

    path = {
    cocos2d::Vec2(100 + 50, 400 + 75),
    cocos2d::Vec2(400 + 50, 400 + 75),
    cocos2d::Vec2(400 + 50, 300 + 75),
    cocos2d::Vec2(600 + 50, 300 + 75),
    cocos2d::Vec2(600 + 50, 200 + 75),
    cocos2d::Vec2(900 + 50, 200 + 75),
    cocos2d::Vec2(900 + 50, 0 + 75),
    cocos2d::Vec2(1200 + 50, 0 + 75),
    cocos2d::Vec2(1200 + 50, 350 + 75)
    };

    path1= {
    cocos2d::Vec2(100 + 50, 200 + 75),
    cocos2d::Vec2(300 + 50, 200 + 75),
    cocos2d::Vec2(300 + 50, 100 + 75),
    cocos2d::Vec2(500 + 50, 100 + 75),
    cocos2d::Vec2(500 + 50, 0 + 75),
    cocos2d::Vec2(1200 + 50, 0 + 75),
    cocos2d::Vec2(1200 + 50, 350 + 75)
    };

    Sprite* gameProgress = Sprite::create("Rabbit.png");
    gameProgress->setPosition(Vec2(420, 765));
    gameProgress->runAction(cocos2d::MoveBy::create(95, Vec2(400, 0)));
    this->addChild(gameProgress, 4);

    auto createRabbitUp = CallFunc::create([=]() {initMonster(1); });
    auto createFastrUp = CallFunc::create([=]() {initMonster(2); });
    auto createFlyingUp = CallFunc::create([=]() {initMonster(3); });
    auto createRabbitDown = CallFunc::create([=]() {initMonster(4); });
    auto createFastrDown = CallFunc::create([=]() {initMonster(5); });
    auto createFlyingDown = CallFunc::create([=]() {initMonster(6); });

    runAction(Sequence::create(
        DelayTime::create(2), createRabbitUp,
        DelayTime::create(2), createFastrUp,
        DelayTime::create(2), createRabbitUp,
        DelayTime::create(2), createFastrUp,

        DelayTime::create(12), createFlyingDown,
        DelayTime::create(2), createRabbitDown,
        DelayTime::create(2), createFlyingDown,
        DelayTime::create(2), createRabbitDown,
        DelayTime::create(2), createFastrDown,

        DelayTime::create(12), createRabbitDown,
        DelayTime::create(2), createRabbitUp,
        DelayTime::create(2), createFlyingDown,
        DelayTime::create(2), createRabbitUp,
        DelayTime::create(2), createFlyingDown,
        DelayTime::create(2), createFastrUp,

        DelayTime::create(12), createFastrDown,
        DelayTime::create(2), createRabbitUp,
        DelayTime::create(2), createFlyingDown,
        DelayTime::create(2), createRabbitUp,
        DelayTime::create(2), createFlyingDown,

        DelayTime::create(12), createFastrDown,
        DelayTime::create(2), createRabbitUp,
        DelayTime::create(2), createFlyingDown,
        DelayTime::create(2), createRabbitUp,
        DelayTime::create(2), createFlyingDown,
        DelayTime::create(2), createFastrUp,
        DelayTime::create(1), createFlyingDown,
        CallFunc::create([=]() {monsterFlag = true; }),
        nullptr));
    return true;
}
