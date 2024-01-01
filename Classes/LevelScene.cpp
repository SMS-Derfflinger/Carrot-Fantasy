#include "LevelScene.h"
#include "GameScene.h"
#include "SceneMain.h"
#include "UpScene.h"
#include "audio/include/SimpleAudioEngine.h"
USING_NS_CC;

LevelScene* LevelScene::create()
{
    LevelScene* scene = new LevelScene();
    if (scene && scene->init())
    {
        scene->autorelease();
        return scene;
    }
    else
    {
        delete scene;
        return nullptr;
    }
}

bool LevelScene::init()
{
    if (!Scene::init())
    {
        return false;
    }
    // 背景
    auto background = Sprite::create("level.png");
    background->setPosition(Vec2(650, 400));
    this->addChild(background);
    //升级界面
    auto upgradeButton = MenuItemImage::create("UpgradePicture.png", "UpgradePicture.png", CC_CALLBACK_1(LevelScene::enterUpgradeScene, this));
    upgradeButton->setPosition(Vec2(1100, 100));





    // 选择关卡按钮
    auto level1Button = MenuItemImage::create("haibao1-1.png", "haibao1-1.png", CC_CALLBACK_1(LevelScene::selectLevel1, this));
    auto level2Button = MenuItemImage::create("haibao2-1.png", "haibao2-1.png", CC_CALLBACK_1(LevelScene::selectLevel2, this));;
    auto level3Button = MenuItemImage::create("haibao3-1.png", "haibao3-1.png", CC_CALLBACK_1(LevelScene::selectLevel3, this));
    level1Button->setPosition(Vec2(200, 400));
    level2Button->setPosition(Vec2(600, 400));
    level3Button->setPosition(Vec2(1000, 400));

    m_level1Button = level1Button;
    m_level2Button = level2Button;
    m_level3Button = level3Button;

    // 设置初始的图片
    m_level1Button->setNormalImage(Sprite::create("haibao1-1.png"));
    m_level2Button->setNormalImage(Sprite::create("suo2-1.png"));
    m_level3Button->setNormalImage(Sprite::create("suo3-1.png"));
    //设置初始金额
    money = 0;
    // 显示 money 数量的 Label
    auto background1 = Sprite::create("qian.png"); // 使用指定的图片文件创建 Sprite 对象作为背景
    background1->setPosition(Vec2(100, 700)); // 设置钱包
    this->addChild(background1);

    m_moneyLabel = Label::createWithTTF("      0", "fonts/Marker Felt.ttf", 32);
    m_moneyLabel->setPosition(Vec2(100, 700));
    this->addChild(m_moneyLabel);


    auto menu = Menu::create(level1Button, level2Button, level3Button, upgradeButton, nullptr);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu);

    // 初始化按钮状态
    m_unlockedLevel1 = true;
    m_unlockedLevel2 = false;
    m_unlockedLevel3 = false;
    return true;
}


void LevelScene::selectLevel1(Ref* sender)
{

    // 创建并添加遮罩层
    auto mask = Sprite::create("mubu.jpg");
    mask->setPosition(Vec2(0, 320)); // 设置初始位置在屏幕外
    this->addChild(mask, 1);

    // 移动遮罩层
    auto moveAction = MoveBy::create(1.0f, Vec2(1960, 0)); // 移动到指定位置
    auto removeAction = RemoveSelf::create();
    auto sequence = Sequence::create(moveAction, removeAction, nullptr);
    mask->runAction(sequence);

    //停下主音乐
    CocosDenshion::SimpleAudioEngine::getInstance()->stopBackgroundMusic();

    m_gameScene = Scene1::createScene(1, this);             // 传递关卡编号
    Director::getInstance()->pushScene(m_gameScene);
}

void LevelScene::selectLevel2(Ref* sender)
{
    if (m_unlockLevel >= 2) // 如果第二关已解锁
    {
        // 创建并添加遮罩层
        auto mask = Sprite::create("mubu.jpg");
        mask->setPosition(Vec2(0, 320)); // 设置初始位置在屏幕外
        this->addChild(mask, 1);

        // 移动遮罩层
        auto moveAction = MoveBy::create(1.0f, Vec2(1960, 0)); // 移动到指定位置
        auto removeAction = RemoveSelf::create();
        auto sequence = Sequence::create(moveAction, removeAction, nullptr);
        mask->runAction(sequence);

        //停下主音乐
        CocosDenshion::SimpleAudioEngine::getInstance()->stopBackgroundMusic();

        m_gameScene = Scene2::createScene(2, this); // 传递关卡编号和 LevelScene 场景的指针
        Director::getInstance()->pushScene(m_gameScene);
    }
}

void LevelScene::selectLevel3(Ref* sender)
{
    if (m_unlockedLevel3) // 如果第三关已解锁
    {
        // 创建并添加遮罩层
        auto mask = Sprite::create("mubu.jpg");
        mask->setPosition(Vec2(0, 320)); // 设置初始位置在屏幕外
        this->addChild(mask, 1);

        // 移动遮罩层
        auto moveAction = MoveBy::create(1.0f, Vec2(1960, 0)); // 移动到指定位置
        auto removeAction = RemoveSelf::create();
        auto sequence = Sequence::create(moveAction, removeAction, nullptr);
        mask->runAction(sequence);

        //停下主音乐
        CocosDenshion::SimpleAudioEngine::getInstance()->stopBackgroundMusic();

        m_gameScene = Scene3::createScene(3, this); // 传递关卡编号和 LevelScene 场景的指针
        Director::getInstance()->pushScene(m_gameScene);
    }
}
void LevelScene::updateButtonState()
{
    m_moneyLabel->setString("       " + std::to_string(money));
    if (m_unlockedLevel2)
    {
        m_level2Button->setNormalImage(Sprite::create("haibao2-1.png")); // 解锁后的图片
    }
    else
    {
        m_level2Button->setNormalImage(Sprite::create("suo2-1.png")); // 未解锁的图片
    }

    if (m_unlockedLevel3)
    {
        m_level3Button->setNormalImage(Sprite::create("haibao3-1.png")); // 解锁后的图片
    }
    else
    {
        m_level3Button->setNormalImage(Sprite::create("suo3-1.png")); // 未解锁的图片
    }

}
void LevelScene::unlockLevel(int level)
{
    m_unlockLevel = level;

    if (level == 2)
    {
        m_unlockedLevel2 = true;
    }
    else if (level == 3)
    {
        m_unlockedLevel3 = true;
    }

    updateButtonState(); // 更新按钮状态和图片
}
void LevelScene::consumeMoney(int n) {
    money = money - n;
}
int LevelScene::getMoney() {
    return money;

}
void LevelScene::enterUpgradeScene(Ref* sender)
{
    auto upgradeScene = UpScene::create(this);
    Director::getInstance()->pushScene(upgradeScene);
}
//获取技能等级与返回
void LevelScene::upgradeItem1() {
    skill1 += 1;
}
//void LevelScene::upgradeItem2() {
//    skill2 += 1;
//}
int LevelScene::getItem1Level() {
    return skill1;
}
//int LevelScene::getItem2Level() {
//    return skill2;
//}