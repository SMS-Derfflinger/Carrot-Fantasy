//#include "SceneMain.h"
//#include "GameScene.h"
//#include "LevelScene.h"
//#include "audio/include/SimpleAudioEngine.h"
//USING_NS_CC;
//
//
//GameScene* GameScene::create(int level, LevelScene* levelScene)
//{
//    GameScene* scene = new GameScene();
//    if (scene && scene->init(level, levelScene))
//    {
//        scene->autorelease();
//        return scene;
//    }
//    else
//    {
//        delete scene;
//        return nullptr;
//    }
//}
//
//bool GameScene::init(int level, LevelScene* levelScene)
//{
//    if (!Scene::init())
//    {
//        return false;
//    }
//    
//    // 创建并添加遮罩层
//    auto mask = Sprite::create("mubu.jpg");
//    mask->setPosition(Vec2(0, 320)); // 设置初始位置在屏幕外
//    this->addChild(mask, 1);
//
//    // 移动遮罩层
//    auto moveAction = MoveBy::create(1.0f, Vec2(1960, 0)); // 移动到指定位置
//    auto removeAction = RemoveSelf::create();
//    auto sequence = Sequence::create(moveAction, removeAction, nullptr);
//    mask->runAction(sequence);
//
//    m_level = level;
//    m_levelScene = levelScene; // 保存关卡选择场景的指针
//    int ml = levelScene->m_unlockLevel;
//
//    // 在这里根据关卡编号加载对应的游戏资源和逻辑
//
//    // ... 其他初始化代码 ...
//
//    // 添加一个按钮，用于表示游戏完成
//    auto completeButton = MenuItemImage::create(
//        "button_normal.png",
//        "button_selected.png",
//        CC_CALLBACK_0(GameScene::onGameComplete, this));
//    auto menu = Menu::create(completeButton, nullptr);
//    levelScene->money = levelScene->money + 50;
//    menu->setPosition(Vec2(650, 420)); // 设置按钮位置
//    addChild(menu);
//
//    return true;
//}
//
//void GameScene::onGameComplete()
//{
//    // 游戏完成时调用此函数
//    if (m_levelScene)
//    {
//        //音乐
//        CocosDenshion::SimpleAudioEngine::getInstance()->preloadBackgroundMusic("main.mp3");
//        CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic("main.mp3", true);
//
//        int nextLevel = m_level + 1;
//        m_levelScene->updateScene(nextLevel, 1); // 解锁下一关
//        Director::getInstance()->popScene();  // 返回到上一个场景
//    }
//}