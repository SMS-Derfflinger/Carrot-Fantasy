#include "SceneBase.h"
#include "SimpleAudioEngine.h"//Cocos2d-x游戏引擎中的音频引擎库的头文件
#include "Obstacle.h"
#include "Monster.h"
#include "Tower.h"
#include "TowerPosition.h"
#include "ui/CocosGUI.h"
#include "levelScene.h"

USING_NS_CC; //using namespace cocos2d

Sprite* plusIcon;

SceneBase* SceneBase::createScene(int level, LevelScene* levelScene)
{
    SceneBase* scene = new SceneBase();
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

cocos2d::Vec2 SceneBase::getCarrotPosition() const
{
    return this->carrotPosition;
}

void SceneBase::setCarrotPosition(cocos2d::Vec2 position)
{
    this->carrotPosition = position;
}

void SceneBase::update(float delta)
{
    time += delta;
    if (monsterFlag)
    {
        int num = 0;
        // 遍历场景中的所有节点
        for (auto child : this->getChildren())
        {
            // 判断该节点是否为 Monster 类型
            auto monster = dynamic_cast<Monster*>(child);
            if (monster != nullptr)
            {
                num++;
            }
        }
        if (num == 0 && carrotHP > 0)
        {
            this->setButton(true);
        }
    }
}

void SceneBase::takeCarrotDamage(int damage)
{
    if (carrotHP > damage)
    {
        carrotHP -= damage;
        if (carrotHP == 9)
        {
            this->removeChild(m_carrot);
            Sprite* Carrot7_9 = Sprite::create("luobo7-9.png");
            Carrot7_9->setPosition(carrotPosition);
            this->m_carrot = Carrot7_9;
            this->addChild(Carrot7_9, 1);
        }
        if (carrotHP == 6)
        {
            this->removeChild(m_carrot);
            Sprite* Carrot4_6 = Sprite::create("luobo4-6.png");
            Carrot4_6->setPosition(carrotPosition);
            this->m_carrot = Carrot4_6;
            this->addChild(Carrot4_6, 1);
        }
        if (carrotHP == 3)
        {
            this->removeChild(m_carrot);
            Sprite* Carrot1_3 = Sprite::create("luobo1-3.png");
            Carrot1_3->setPosition(carrotPosition);
            this->m_carrot = Carrot1_3;
            this->addChild(Carrot1_3, 1);
        }
    }
    else
    {
        carrotHP = 0;
        this->setButton(false);
    }
}

/*
* 显示层数：
* 0层：地图背景
* 1层：萝卜、炮塔的底座、钱
* 2层：放置的炮塔、子弹
* 3层：炮塔位置的加号、加号上面的可选炮塔按钮
* 4层：进度条
* 5层：结束界面
* 6层：结束界面上面的按钮
*/
void SceneBase::initScene(std::string& mapName)
{
    auto map = TMXTiledMap::create(mapName);
    this->addChild(map, 0);     // 添加到场景中，显示在第0层

    // 获取萝卜对象层
    TMXObjectGroup* carrotObjects = map->getObjectGroup("Carrot");

    // 获取萝卜对象的位置信息
    const auto& firstCarrotObject = carrotObjects->getObjects().at(0);
    float xC = firstCarrotObject.asValueMap().at("x").asFloat() + 60;
    float yC = firstCarrotObject.asValueMap().at("y").asFloat() + 70;

    // 创建萝卜并放置在地图上的位置
    Vec2 carrotPos = Vec2(xC, yC);
    Sprite* carrot = Sprite::create("luobo.png");
    carrot->setPosition(carrotPos);
    this->addChild(carrot, 1);      // 添加到场景中，显示在第1层，确保在地图上方显示
    this->carrotPosition = carrotPos;
    this->m_carrot = carrot;

    TMXObjectGroup* towerPositions = map->getObjectGroup("TowerPosition");
    // 处理位置对象
    ValueVector towerPositionsVector = towerPositions->getObjects();

    for (const auto& towerPosition : towerPositionsVector)
    {
        // 获取炮塔位置对象的位置信息
        float xP = towerPosition.asValueMap().at("x").asFloat() + 50;
        float yP = towerPosition.asValueMap().at("y").asFloat() + 50;

        // 创建炮塔位置并放置在地图上
        Vec2 position = Vec2(xP, yP);
        TowerPosition* towerPos = TowerPosition::create();
        towerPos->setPosition(position);
        towerPos->setVisible(false);        // 初始化时设置为隐藏状态
        this->addChild(towerPos, 3);        // 添加到场景中，显示在第3层，确保在地图上方显示

    }

    // 添加鼠标事件监听器，用于处理炮塔位置对象的显示和隐藏
    auto listener = EventListenerTouchOneByOne::create();
    listener->setSwallowTouches(true);
    listener->onTouchBegan = [&](Touch* touch, Event* event) {
        auto children = this->getChildren();
        for (Node* child : children)
        {
            TowerPosition* towerPos = dynamic_cast<TowerPosition*>(child);
            // 被点击的方块
            if (towerPos && towerPos->getBoundingBox().containsPoint(touch->getLocation()))
            {
                // 当前位置有塔
                if (towerPos->towerofThisPosition)
                {
                   // towerPos->setVisible(false);

                    // 创建按钮
                    Vec2 positionUp = Vec2(40, 120);
                    Vec2 positionDelete = Vec2(40, -40);

                    if (dynamic_cast<BottleTower_1*>(towerPos->towerofThisPosition)) {
                        // 升级按钮
                        auto towerUp = cocos2d::ui::Button::create("BottleUpgrade1.png", "BottleUpgrade1.png", "BottleUpgradeUn1.png");
                        towerUp->setPosition(positionUp);
                        //towerUp->addClickEventListener(CC_CALLBACK_1(SceneBase::updateBottle1, this));  // 添加按钮点击回调函数
                        towerPos->addChild(towerUp, 10, "BottleButton");
                        // 设置点击状态
                        if (this->moneyScene >= 150)
                        {
                            towerUp->setEnabled(true);
                        }
                        else
                        {
                            towerUp->setEnabled(false);
                        }
                        // 删除按钮
                        auto towerDelete = cocos2d::ui::Button::create("BottleRemove1.png", "BottleRemove1.png");
                        towerDelete->setPosition(positionDelete);
                        towerDelete->addClickEventListener(CC_CALLBACK_1(SceneBase::createBottle, this));  // 添加按钮点击回调函数
                        towerPos->addChild(towerDelete, 0, "BottleButton");
                    }
                    else if (dynamic_cast<BottleTower_2*>(towerPos->towerofThisPosition)) {
                        // 升级按钮
                        auto towerUp = cocos2d::ui::Button::create("BottleUpgrade2.png", "BottleUpgrade2.png", "BottleUpgradeUn2.png");
                        towerUp->setPosition(positionUp);
                        towerUp->addClickEventListener(CC_CALLBACK_1(SceneBase::createBottle, this));  // 添加按钮点击回调函数
                        towerPos->addChild(towerUp, 0, "BottleButton");
                        // 设置点击状态
                        if (this->moneyScene >= 250)
                        {
                            towerUp->setEnabled(true);
                        }
                        else
                        {
                            towerUp->setEnabled(false);
                        }
                        // 删除按钮
                        auto towerDelete = cocos2d::ui::Button::create("BottleRemove2.png", "BottleRemove2.png");
                        towerDelete->setPosition(positionDelete);
                        towerDelete->addClickEventListener(CC_CALLBACK_1(SceneBase::createBottle, this));  // 添加按钮点击回调函数
                        towerPos->addChild(towerDelete, 0, "BottleButton");
                    }
                    else if (dynamic_cast<BottleTower_3*>(towerPos->towerofThisPosition)) {
                        // 删除按钮
                        auto towerDelete = cocos2d::ui::Button::create("BottleRemove3.png", "BottleRemove3.png");
                        towerDelete->setPosition(positionDelete);
                        towerDelete->addClickEventListener(CC_CALLBACK_1(SceneBase::createBottle, this));  // 添加按钮点击回调函数
                        towerPos->addChild(towerDelete, 0, "BottleButton");
                    }
                    else if (dynamic_cast<StarTower_1*>(towerPos->towerofThisPosition)) {
                        // 升级按钮
                        auto towerUp = cocos2d::ui::Button::create("StarUpgrade1.png", "StarUpgrade1.png", "StarUpgradeUn1.png");
                        towerUp->setPosition(positionUp);
                        towerUp->addClickEventListener(CC_CALLBACK_1(SceneBase::createBottle, this));  // 添加按钮点击回调函数
                        towerPos->addChild(towerUp, 0, "BottleButton");
                        // 设置点击状态
                        if (this->moneyScene >= 150)
                        {
                            towerUp->setEnabled(true);
                        }
                        else
                        {
                            towerUp->setEnabled(false);
                        }
                        // 删除按钮
                        auto towerDelete = cocos2d::ui::Button::create("BottleRemove1.png", "BottleRemove1.png");
                        towerDelete->setPosition(positionDelete);
                        towerDelete->addClickEventListener(CC_CALLBACK_1(SceneBase::createBottle, this));  // 添加按钮点击回调函数
                        towerPos->addChild(towerDelete, 0, "BottleButton");
                    }
                    else if (dynamic_cast<StarTower_2*>(towerPos->towerofThisPosition)) {
                        // 升级按钮
                        auto towerUp = cocos2d::ui::Button::create("StarUpgrade2.png", "StarUpgrade2.png", "StarUpgradeUn2.png");
                        towerUp->setPosition(positionUp);
                        towerUp->addClickEventListener(CC_CALLBACK_1(SceneBase::createBottle, this));  // 添加按钮点击回调函数
                        towerPos->addChild(towerUp, 0, "BottleButton");
                        // 设置点击状态
                        if (this->moneyScene >= 150)
                        {
                            towerUp->setEnabled(true);
                        }
                        else
                        {
                            towerUp->setEnabled(false);
                        }
                        // 删除按钮
                        auto towerDelete = cocos2d::ui::Button::create("BottleRemove3.png", "BottleRemove3.png");
                        towerDelete->setPosition(positionDelete);
                        towerDelete->addClickEventListener(CC_CALLBACK_1(SceneBase::createBottle, this));  // 添加按钮点击回调函数
                        towerPos->addChild(towerDelete, 0, "BottleButton");
                    }
                    else if (dynamic_cast<StarTower_3*>(towerPos->towerofThisPosition)) {
                        // 删除按钮
                        auto towerDelete = cocos2d::ui::Button::create("StarRemove3.png", "StarRemove3.png");
                        towerDelete->setPosition(positionDelete);
                        towerDelete->addClickEventListener(CC_CALLBACK_1(SceneBase::createBottle, this));  // 添加按钮点击回调函数
                        towerPos->addChild(towerDelete, 0, "BottleButton");
                    }
                    else if (dynamic_cast<SunflowerTower_1*>(towerPos->towerofThisPosition)) {
                        // 升级按钮
                        auto towerUp = cocos2d::ui::Button::create("StarUpgrade1.png", "StarUpgrade1.png", "BottleUpgradeUn3.png");
                        towerUp->setPosition(positionUp);
                        towerUp->addClickEventListener(CC_CALLBACK_1(SceneBase::createBottle, this));  // 添加按钮点击回调函数
                        towerPos->addChild(towerUp, 0, "BottleButton");
                        // 设置点击状态
                        if (this->moneyScene >= 150)
                        {
                            towerUp->setEnabled(true);
                        }
                        else
                        {
                            towerUp->setEnabled(false);
                        }
                        // 删除按钮
                        auto towerDelete = cocos2d::ui::Button::create("BottleRemove1.png", "BottleRemove1.png");
                        towerDelete->setPosition(positionDelete);
                        towerDelete->addClickEventListener(CC_CALLBACK_1(SceneBase::createBottle, this));  // 添加按钮点击回调函数
                        towerPos->addChild(towerDelete, 0, "BottleButton");
                    }
                    else if (dynamic_cast<SunflowerTower_2*>(towerPos->towerofThisPosition)) {
                        // 升级按钮
                        auto towerUp = cocos2d::ui::Button::create("StarUpgrade2.png", "StarUpgrade2.png", "StarUpgradeUn2.png");
                        towerUp->setPosition(positionUp);
                        towerUp->addClickEventListener(CC_CALLBACK_1(SceneBase::createBottle, this));  // 添加按钮点击回调函数
                        towerPos->addChild(towerUp, 0, "BottleButton");
                        // 设置点击状态
                        if (this->moneyScene >= 150)
                        {
                            towerUp->setEnabled(true);
                        }
                        else
                        {
                            towerUp->setEnabled(false);
                        }
                        // 删除按钮
                        auto towerDelete = cocos2d::ui::Button::create("BottleRemove3.png", "BottleRemove3.png");
                        towerDelete->setPosition(positionDelete);
                        towerDelete->addClickEventListener(CC_CALLBACK_1(SceneBase::createBottle, this));  // 添加按钮点击回调函数
                        towerPos->addChild(towerDelete, 0, "BottleButton");
                    }
                    else if (dynamic_cast<SunflowerTower_3*>(towerPos->towerofThisPosition)) {
                        // 删除按钮
                        auto towerDelete = cocos2d::ui::Button::create("StarRemove1.png", "StarRemove1.png");
                        towerDelete->setPosition(positionDelete);
                        towerDelete->addClickEventListener(CC_CALLBACK_1(SceneBase::createBottle, this));  // 添加按钮点击回调函数
                        towerPos->addChild(towerDelete, 0, "BottleButton");
                    }
                    
                }
                // 没有塔，显示建造界面
                else {
                    towerPos->setVisible(true);
                    // 创建按钮
                    Vec2 positionButtonBottle = Vec2(40, 120);
                    Vec2 positionButtonStar = Vec2(-40, 120);
                    Vec2 positionButtonSunflower = Vec2(120, 120);
                    Vec2 positionCheck = towerPos->getPosition();
                    if (positionCheck.x == 50)      //如果位置紧贴左边缘，对建立的按钮相对坐标进行处理，使按钮显示在右侧
                    {
                        positionButtonBottle = Vec2(120, 40);
                        positionButtonStar = Vec2(120, 120);
                        positionButtonSunflower = Vec2(120, -40);
                    }
                    auto buttonBottle = cocos2d::ui::Button::create("BottleButton.png", "BottleButton.png", "BottleButtonUn.png");
                    buttonBottle->setPosition(positionButtonBottle);
                    buttonBottle->addClickEventListener(CC_CALLBACK_1(SceneBase::createBottle, this));  // 添加按钮点击回调函数
                    towerPos->addChild(buttonBottle, 0, "BottleButton");
                    // 设置点击状态
                    if (this->moneyScene >= 100) {
                        buttonBottle->setEnabled(true);
                    }
                    else {
                        buttonBottle->setEnabled(false);
                    }

                    towerPos->setVisible(true);
                    // 创建按钮
                    
                    auto buttonStar = cocos2d::ui::Button::create("StarButton.png", "StarButton.png", "StarButtonUn.png");
                    buttonStar->setPosition(positionButtonStar);
                    buttonStar->addClickEventListener(CC_CALLBACK_1(SceneBase::createStar, this));  // 添加按钮点击回调函数
                    towerPos->addChild(buttonStar, 0, "StarButton");
                    // 设置点击状态
                    if (this->moneyScene >= 200) {
                        buttonStar->setEnabled(true);
                    }
                    else {
                        buttonStar->setEnabled(false);
                    }

                    towerPos->setVisible(true);
                    // 创建按钮
                    
                    auto buttonSunflower = cocos2d::ui::Button::create("SunflowerButton.png", "SunflowerButton.png", "SunflowerButtonUn.png");
                    buttonSunflower->setPosition(positionButtonSunflower);
                    buttonSunflower->addClickEventListener(CC_CALLBACK_1(SceneBase::createSunflower, this));  // 添加按钮点击回调函数
                    towerPos->addChild(buttonSunflower, 0, "SunflowerButton");
                    // 设置点击状态
                    if (this->moneyScene >= 200) {
                        buttonSunflower->setEnabled(true);
                    }
                    else {
                        buttonSunflower->setEnabled(false);
                    }
                }
            }
            // 没有被点击的方块
            else if (towerPos)
            {
                towerPos->setVisible(false);
                
                // 查找和移除所有的建造按钮
                cocos2d::ui::Button* spriteBottle = static_cast<cocos2d::ui::Button*>(this->getChildByName("BottleButton"));
                if (spriteBottle) {
                    // 子节点存在，可以进行移除操作
                    this->removeChildByName("BottleButton");
                }

                cocos2d::ui::Button* spriteStar = static_cast<cocos2d::ui::Button*>(this->getChildByName("StarButton"));
                if (spriteStar) {
                    // 子节点存在，可以进行移除操作
                    this->removeChildByName("StarButton");
                }

                cocos2d::ui::Button* spriteSunflower = static_cast<cocos2d::ui::Button*>(this->getChildByName("SunflowerButton"));
                if (spriteSunflower) {
                    // 子节点存在，可以进行移除操作
                    this->removeChildByName("SunflowerButton");
                }
            }
        }
        return true;
        };

    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

}

void SceneBase::menuCloseCallback(Ref* pSender)
{
    //这个函数会停止游戏循环，并释放所有的资源。
    Director::getInstance()->end();

    //如果希望在iOS中返回原生界面而不是退出应用程序，可以注释掉这个函数，并调用下面的代码，
    //触发一个名为“game_scene_close_event”的自定义事件，由RootViewController.mm文件中的代码处理。

    //EventCustom customEndEvent("game_scene_close_event");
    //_eventDispatcher->dispatchEvent(&customEndEvent);
}

void SceneBase::createBottle(cocos2d::Ref* sender)
{
    // 在当前位置创建炮塔
    auto button = dynamic_cast<cocos2d::ui::Button*>(sender);
    if (button)
    {
        auto tower = BottleTower_1::create();  // 创建炮塔对象
        if (moneyScene >= tower->getConsumption())
        {
            auto bottom = Sprite::create("Bottom.png");
            bottom->setPosition(button->getParent()->getPosition());
            tower->setPosition(button->getParent()->getPosition());  // 设置炮塔位置
            auto thisTowerPosition = dynamic_cast<TowerPosition*> (button->getParent());
            if (thisTowerPosition)
            {
                thisTowerPosition->towerofThisPosition = tower;
            }
            this->addChild(bottom, 1);
            this->addChild(tower, 2);  // 将炮塔添加到场景中
            button->getParent()->setVisible(false);

            this->updateMoney(-100);
        }
    }
}

void SceneBase::createStar(cocos2d::Ref* sender)
{
    // 在当前位置创建星星炮塔
    auto button = dynamic_cast<cocos2d::ui::Button*>(sender);
    if (button)
    {
        auto tower = StarTower_1::create();  // 创建炮塔对象
        if (moneyScene >= tower->getConsumption())
        {
            //auto bottom = Sprite::create("Bottom.png");
            //bottom->setPosition(button->getParent()->getPosition());
            tower->setPosition(button->getParent()->getPosition());  // 设置炮塔位置
            auto thisTowerPosition = dynamic_cast<TowerPosition*> (button->getParent());
            if (thisTowerPosition)
            {
                thisTowerPosition->towerofThisPosition = tower;
            }
            //this->addChild(bottom, 1);
            this->addChild(tower, 2);  // 将炮塔添加到场景中
            button->getParent()->setVisible(false);

            this->updateMoney(-200);
        }
    }
}

void SceneBase::createSunflower(cocos2d::Ref* sender)
{
    // 在当前位置创建太阳花炮塔
    auto button = dynamic_cast<cocos2d::ui::Button*>(sender);
    if (button)
    {
        auto tower = SunflowerTower_1::create();  // 创建炮塔对象
        if (moneyScene >= tower->getConsumption())
        {
            auto bottom = Sprite::create("Bottom.png");
            bottom->setPosition(button->getParent()->getPosition());
            tower->setPosition(button->getParent()->getPosition());  // 设置炮塔位置
            auto thisTowerPosition = dynamic_cast<TowerPosition*> (button->getParent());
            if (thisTowerPosition)
            {
                thisTowerPosition->towerofThisPosition = tower;
            }
            this->addChild(bottom, 1);
            this->addChild(tower, 2);  // 将炮塔添加到场景中
            button->getParent()->setVisible(false);

            this->updateMoney(-200);
        }
    }
}

// on "init" you need to initialize your instance
bool SceneBase::init(int level, LevelScene* levelScene)
{
    // 调用了父类Scene的init()函数进行初始化，如果初始化失败，则返回false
    if (!Scene::init())
    {
        return false;
    }

    m_levelScene = levelScene;
    // 创建定时器，定时更新怪物状态
    scheduleUpdate();
    return true;
}


void SceneBase::setButton(bool flag)
{
    if (flag)
    {
        auto closeWin = Sprite::create("WinPicture.png");
        closeWin->setPosition(Vec2(650, 400));
        this->addChild(closeWin, 5, "WinBackground");

        auto continueGame = MenuItemImage::create(
            "ContinueGame.png",
            "ContinueGame.png",
            CC_CALLBACK_0(SceneBase::onGameWin, this));
        auto menuContinue = Menu::create(continueGame, nullptr);
        menuContinue->setPosition(Vec2(650, 265));    // 设置按钮位置
        this->addChild(menuContinue, 6, "ContinueGame");
        //Director::getInstance()->pause();           // 暂停游戏
    }
    else
    {
        auto closeFail = Sprite::create("FailPicture.png");
        closeFail->setPosition(Vec2(650, 420));
        this->addChild(closeFail, 5, "FailBackground");

        auto goBack = MenuItemImage::create(
            "GoBack.png",
            "GoBack.png",
            CC_CALLBACK_0(SceneBase::onGameFail, this));
        auto menuBack = Menu::create(goBack, nullptr);
        menuBack->setPosition(Vec2(650, 265));      // 设置按钮位置
        this->addChild(menuBack, 6, "GoBack");
        Director::getInstance()->pause();           // 暂停游戏
    }
}

void SceneBase::onGameWin()
{
    // 游戏完成时调用此函数
    if (m_levelScene)
    {
        //Director::getInstance()->resume();          // 恢复游戏
        int nextLevel = m_level + 1;
        m_levelScene->money += 100;
        m_levelScene->unlockLevel(nextLevel);       // 解锁下一关
        Director::getInstance()->popScene();        // 返回到上一个场景
    }
}

void SceneBase::onGameFail()
{
    // 游戏完成时调用此函数
    if (m_levelScene)
    {
        Director::getInstance()->resume();          // 恢复游戏
        Director::getInstance()->popScene();        // 返回到上一个场景
    }
}

void SceneBase::addMoney(int money)
{
    this->moneyScene += money;
}

void SceneBase::updateMoney(int money)
{
    moneyScene += money;
    this->removeChild(m_lable);
    std::string text = std::to_string(moneyScene); // 将数字转换为字符串
    auto lable = Label::createWithTTF(text, "fonts/arial.ttf", 48);
    lable->setPosition(Vec2(260, 763));
    this->m_lable = lable;
    this->addChild(m_lable, 1);
}

void SceneBase::updateBottle1(cocos2d::Ref* sender)
{
    // 在当前位置创建炮塔
    auto button = dynamic_cast<cocos2d::ui::Button*>(sender);
    if (button)
    {
        auto tower = BottleTower_2::create();  // 创建炮塔对象
        if (moneyScene >= tower->getConsumption())
        {
            button->getParent()->removeAllChildren();
            auto bottom = Sprite::create("Bottom.png");
            bottom->setPosition(button->getParent()->getPosition());
            tower->setPosition(button->getParent()->getPosition());  // 设置炮塔位置
            auto thisTowerPosition = dynamic_cast<TowerPosition*> (button->getParent());
            if (thisTowerPosition)
            {
                thisTowerPosition->towerofThisPosition = tower;
            }
            this->addChild(bottom, 1);
            this->addChild(tower, 2);  // 将炮塔添加到场景中
            button->getParent()->setVisible(false);

            this->updateMoney(-150);
        }
    }
}