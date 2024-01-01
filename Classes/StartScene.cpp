#include "StartScene.h"
#include "LevelScene.h"
#include "audio/include/SimpleAudioEngine.h"

USING_NS_CC;

StartScene* StartScene::create()
{
    StartScene* scene = new StartScene();
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

bool StartScene::init()
{
    if (!Scene::init())
    {
        return false;
    }

    // ±³¾°
    auto background = Sprite::create("open.png");
    background->setPosition(Vec2(650, 400));
    this->addChild(background);

    // ¿ªÊ¼°´Å¥
    auto startButton = MenuItemImage::create("button_normal.png", "button_selected.png", CC_CALLBACK_1(StartScene::startGame, this));
    startButton->setPosition(Vec2(650, 500));

    CocosDenshion::SimpleAudioEngine::getInstance()->preloadBackgroundMusic("main.mp3");
    CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic("main.mp3", true);

    auto menu = Menu::create(startButton, nullptr);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu);

    return true;
}


void StartScene::startGame(Ref* sender)
{
    auto levelScene = LevelScene::create();
    Director::getInstance()->replaceScene(levelScene);
}
