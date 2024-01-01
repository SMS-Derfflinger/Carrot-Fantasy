#include "UpScene.h"
#include "LevelScene.h"
#include "GameScene.h"
USING_NS_CC;

UpScene* UpScene::create(LevelScene* levelScene)
{
    UpScene* scene = new UpScene();
    if (scene && scene->init(levelScene))
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

bool UpScene::init(LevelScene* levelScene)
{
    if (!Scene::init())
    {
        return false;
    }

    m_levelScene = levelScene;

    // 背景
    auto background = Sprite::create("shengji-2.png");
    background->setPosition(Vec2(650, 400));
    this->addChild(background);

    // 金额标签
    // 显示 money 数量的 Label
    auto background1 = Sprite::create("qian.png"); // 使用指定的图片文件创建 Sprite 对象作为背景
    background1->setPosition(Vec2(100, 650)); // 设置钱包
    this->addChild(background1);
    m_moneyLabel = Label::createWithTTF("      " + std::to_string(m_levelScene->getMoney()), "fonts/Marker Felt.ttf", 32);
    m_moneyLabel->setPosition(Vec2(100, 650));
    this->addChild(m_moneyLabel);

    m_item1LevelLabel = Label::createWithTTF("Level " + std::to_string(m_levelScene->getItem1Level()), "fonts/Marker Felt.ttf", 32);
    m_item1LevelLabel->setPosition(Vec2(1000, 630));
    this->addChild(m_item1LevelLabel);

    //m_item2LevelLabel = Label::createWithTTF("Level " + std::to_string(m_levelScene->getItem2Level()), "fonts/Marker Felt.ttf", 32);
    //m_item2LevelLabel->setPosition(Vec2(1000, 430));
    //this->addChild(m_item2LevelLabel);

    // 第一项物品升级按钮
    auto item1Button = MenuItemImage::create("skill1.png", "skill1.png", CC_CALLBACK_1(UpScene::onItem1Button, this));
    item1Button->setPosition(Vec2(850, 550));

    //// 第二项物品升级按钮
    //auto item2Button = MenuItemImage::create("skill2.png", "skill2.png", CC_CALLBACK_1(UpScene::onItem2Button, this));
    //item2Button->setPosition(Vec2(850, 350));

    // 返回按钮
    auto backButton = MenuItemImage::create("exit.png", "exit.png", CC_CALLBACK_1(UpScene::onBackButton, this));
    backButton->setPosition(Vec2(70, 760));

    auto menu = Menu::create(item1Button,  backButton, nullptr);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu);

    return true;
}

void UpScene::onItem1Button(Ref* sender)
{
    int money = m_levelScene->getMoney();
    if (m_levelScene->getItem1Level() < 3) {
        if (money >= 100)
        {
            m_levelScene->consumeMoney(100);
            m_moneyLabel->setString("       " + std::to_string(m_levelScene->getMoney()));

            // 升级第一项物品
            m_levelScene->upgradeItem1();
            int item1Level = m_levelScene->getItem1Level();
            m_item1LevelLabel->setString("Level " + std::to_string(item1Level));
        }
        else
        {
            // 钱不够，无法升级，可以添加提示或弹窗等操作
        }
    }

}

//void UpScene::onItem2Button(Ref* sender)
//{
//    int money = m_levelScene->getMoney();
//    if (m_levelScene->getItem2Level() < 3) {
//        if (money >= 100)
//        {
//            m_levelScene->consumeMoney(100);
//            m_moneyLabel->setString("       " + std::to_string(m_levelScene->getMoney()));
//
//            // 升级第二项物品
//            m_levelScene->upgradeItem2();
//            int item2Level = m_levelScene->getItem2Level();
//            m_item2LevelLabel->setString("Level " + std::to_string(item2Level));
//        }
//        else
//        {
//            // 钱不够，无法升级，可以添加提示或弹窗等操作
//        }
//    }
//}

void UpScene::onBackButton(Ref* sender)
{
    m_levelScene->updateButtonState();
    Director::getInstance()->popScene();
}
