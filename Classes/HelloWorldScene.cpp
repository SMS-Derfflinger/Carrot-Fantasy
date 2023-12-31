//#include "HelloWorldScene.h"
//#include "SimpleAudioEngine.h"//Cocos2d-x游戏引擎中的音频引擎库的头文件
//#include "Obstacle.h"
//#include "Monster.h"
//#include "Tower.h"
//#include "Carrot.h"
//#include "TowerPosition.h"
//#include "ui/CocosGUI.h"
//
//USING_NS_CC; //using namespace cocos2d
//
//Sprite* plusIcon;
//
//Scene* HelloWorld::createScene()
//{
//    return HelloWorld::create();
//}
//// 打印有用的错误消息，而不是在文件不存在时段错误。
//static void problemLoading(const char* filename)
//{
//    printf("Error while loading: %s\n", filename);
//    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
//}
//
//// on "init" you need to initialize your instance
//bool HelloWorld::init()
//{
//    // 调用了父类Scene的init()函数进行初始化，如果初始化失败，则返回false
//    if (!Scene::init())
//    {
//        return false;
//    }
//
//
//    // 从当前路径下获得tmx文件，加载tmx地图并显示
//    std::string file = "level 1.tmx";
//    auto map = TMXTiledMap::create(file);
//    this->addChild(map, 0);     // 添加到场景中，显示在第0层
//
//    // 获取萝卜对象层
//    TMXObjectGroup* carrotObjects = map->getObjectGroup("Carrot");
//
//    // 获取萝卜对象的位置信息
//    const auto& firstCarrotObject = carrotObjects->getObjects().at(0);
//    float xC = firstCarrotObject.asValueMap().at("x").asFloat() + 60;
//    float yC = firstCarrotObject.asValueMap().at("y").asFloat() + 70;
//
//    // 创建萝卜并放置在地图上的位置
//    Vec2 carrotPosition = Vec2(xC, yC);
//    Carrot* carrot = Carrot::create();
//    carrot->setPosition(Vec2(xC, yC));
//    this->addChild(carrot, 1);      // 添加到场景中，显示在第1层，确保在地图上方显示
//
//    TMXObjectGroup* towerPositions = map->getObjectGroup("TowerPosition");
//    // 处理位置对象
//    ValueVector towerPositionsVector = towerPositions->getObjects();
//    
//    for (const auto& towerPosition : towerPositionsVector)
//    {
//        // 获取炮塔位置对象的位置信息
//        float xP = towerPosition.asValueMap().at("x").asFloat() + 50;
//        float yP = towerPosition.asValueMap().at("y").asFloat() + 50;
//
//        // 创建炮塔位置并放置在地图上的位置
//        Vec2 position = Vec2(xP, yP);
//        TowerPosition* towerPos = TowerPosition::create();
//        towerPos->setPosition(position);
//        towerPos->setVisible(false);        // 初始化时设置为隐藏状态
//        this->addChild(towerPos, 1);        // 添加到场景中，显示在第1层，确保在地图上方显示
//
//        float xB = 40;
//        float yB = 100;
//        Vec2 positionButton = Vec2(xB, yB);
//        // 创建按钮
//        auto button = cocos2d::ui::Button::create("CloseNormal.png", "CloseNormal.png");
//        button->setPosition(positionButton);
//        button->addClickEventListener(CC_CALLBACK_1(HelloWorld::onButtonClick, this));  // 添加按钮点击回调函数
//        towerPos->addChild(button, 2);
//    }
//    
//    // 添加鼠标事件监听器，用于处理炮塔位置对象的显示和隐藏
//    auto listener = EventListenerTouchOneByOne::create();
//    listener->setSwallowTouches(true);
//    listener->onTouchBegan = [&](Touch* touch, Event* event)
//        {
//            for (Node* child : this->getChildren())
//            {
//                TowerPosition* towerPos = dynamic_cast<TowerPosition*>(child);
//                if (towerPos && towerPos->getBoundingBox().containsPoint(touch->getLocation()))
//                {
//                    if (towerPos->towerofThisPosition)
//                        towerPos->setVisible(false);
//                    else
//                        towerPos->setVisible(true);
//                }
//                else if (towerPos)
//                {
//                    towerPos->setVisible(false);
//                }
//            }
//            return true;
//        };
//
//    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
//
//
//    //------------------------------------------------------------------------------------------------------------//
//     
//    //int money = 0;
//    //// 通过调用 getInstance() 方法可以获取到当前的导演对象
//    //// 用于获取游戏窗口的可见大小，返回的是一个 Size 对象，包含了窗口的宽度和高度
//    //auto visibleSize = Director::getInstance()->getVisibleSize();
//    //// 用于获取游戏窗口的原点位置，返回的是一个 Vec2 对象，包含了原点的 x 和 y 坐标。
//    //Vec2 origin = Director::getInstance()->getVisibleOrigin();
//
//
//    //// 添加带有“X”图像的菜单项，单击该菜单项可退出程序，您可以修改它。
//    //// 添加“关闭”图标以退出程序，它是一个自动释放对象
//    ////auto closeItem = MenuItemImage::create(
//    ////                                       "CloseNormal.png",
//    ////                                       "CloseSelected.png",
//    ////                                       CC_CALLBACK_1(HelloWorld::menuCloseCallback, this));
//
//    ////if (closeItem == nullptr ||
//    ////    closeItem->getContentSize().width <= 0 ||
//    ////    closeItem->getContentSize().height <= 0)
//    ////{
//    ////    problemLoading("'CloseNormal.png' and 'CloseSelected.png'");
//    ////}
//    ////else
//    ////{
//    ////    float x = origin.x + visibleSize.width - closeItem->getContentSize().width/2;
//    ////    float y = origin.y + closeItem->getContentSize().height/2;
//    ////    closeItem->setPosition(Vec2(x,y));// 紧贴右下角
//    ////}
//    ////// 创建菜单容器，它是一个自动释放对象
//    ////auto menu = Menu::create(closeItem, NULL);
//    ////menu->setPosition(Vec2::ZERO);
//    ////this->addChild(menu, 1);
//
//
//
//    ////auto moveAction = MoveTo::create(3.0f, Vec2(0, 0)); // 在2秒内向右下角移动100个像素
//    ////closeItem->runAction(moveAction);
//
//    ////TestObstacle* obstacle1 = TestObstacle::create();
//    ////obstacle1->setPosition(Vec2(100, 200));
//    ////obstacle1->setObstaclePosition(10, 20, 10, 20);
//    ////this->addChild(obstacle1);
//
//    ////obstacle1->takeDamage(100, money);
//
//    TestMonster* Monster = TestMonster::create();
//    Monster->setPosition(Vec2(200 + 50, 500 + 50));
//    this->addChild(Monster);
//    std::vector<cocos2d::Vec2> path = {
//    cocos2d::Vec2(200 + 50, 100 + 50),
//    cocos2d::Vec2(400 + 50, 100 + 50),
//    cocos2d::Vec2(400 + 50, 300 + 50),
//    cocos2d::Vec2(300 + 50, 300 + 50),
//    cocos2d::Vec2(300 + 50, 500 + 50),
//    cocos2d::Vec2(500 + 50, 500 + 50),
//    cocos2d::Vec2(500 + 50, 100 + 50),
//    cocos2d::Vec2(700 + 50, 100 + 50),
//    cocos2d::Vec2(700 + 50, 300 + 50),
//    cocos2d::Vec2(950 + 50, 300 + 50)
//    };
//    Monster->moveToSequence(path);
//    //Monster->moveTo(Vec2(100, 200));
//
//
//    /*TestMonster* Monster2 = TestMonster::create();
//    Monster2->setPosition(Vec2(500, 700));
//    Monster2->moveTo(Vec2(20, 10));
//    this->addChild(Monster2);
//
//    TestMonster* Monster3 = TestMonster::create();
//    Monster3->setPosition(Vec2(1000, 900));
//    Monster3->moveTo(Vec2(20, 10));
//    this->addChild(Monster3);*/
//
//
//    //TestTower* TestTower = TestTower::create();
//    //TestTower->setPosition(Vec2(50, 50));
//    //this->addChild(TestTower);
//
//
//    //------------------------------------------------------------------------------------------------------------//
//
//
//    // 创建多边形精灵
//    //// 创建多边形精灵
//    //auto triangle = DrawNode::create();
//    //Color4F color(10, 10, 0, 1); // 填充颜色
//
//    //// 定义三角形的三个顶点
//    //Vec2 vertices[] = {
//    //    Vec2(0, 50), // 第一个顶点
//    //    Vec2(-50, -50), // 第二个顶点
//    //    Vec2(50, -50) // 第三个顶点
//    //};
//
//    //// 绘制三角形
//    //triangle->drawPolygon(vertices, 3, color, 0, color); // 参数分别为顶点数组、顶点数量、填充颜色、边框宽度、边框颜色
//
//    //// 设置位置并添加到场景中
//    //triangle->setPosition(Vec2(100, 100));
//    //addChild(triangle);
//
//
//
//
//
//
//
//
//    //Monster->takeDamage(100, money);
//
//
//    //auto sprite = Obstacle::create("cat.png");
//
//    //// 设置精灵的初始位置
//    //sprite->setPosition(Vec2(100,100));
//
//    //// 将精灵添加到场景中
//    //this->addChild(sprite);
//
//    //auto action = MoveTo::create(5.0f, Vec2(10, 10));
//    //sprite->runAction(action);
//    ////auto action = MoveTo::create(5.0f, Vec2(100, 200));
//    ////sprite->runAction(action);
//
//    //this->scheduleOnce([=](float dt) {
//    //    sprite->removeFromParentAndCleanup(true);
//    //    }, 3.0f, "remove_sprite");
//
//
//    /////////////////////////////
//    // 3. add your codes below...
//
//    // add a label shows "Hello World"
//    // create and initialize a label
//
//    // 用于创建一个基于TrueType字体文件的标签对象。
//    //auto label = Label::createWithTTF("Hello World", "fonts/Marker Felt.ttf", 24);//文本内容、字体文件路径和字体大小
//    //if (label == nullptr)
//    //{
//    //    problemLoading("'fonts/Marker Felt.ttf'");
//    //}
//    //else
//    //{
//    //    // position the label on the center of the screen
//    //    label->setPosition(Vec2(origin.x + visibleSize.width/2,
//    //                            origin.y + visibleSize.height - label->getContentSize().height));
//
//    //    // add the label as a child to this layer
//    //    this->addChild(label, 1);
//    //}
//
//     //add "HelloWorld" splash screen"
//     // 
//    //auto sprite = Sprite::create("pic1.png");
//
//
//    //if (sprite == nullptr)
//    //{
//    //    problemLoading("'HelloWorld.png'");
//    //}
//    //else
//    //{
//    //    // position the sprite on the center of the screen
//    //    sprite->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
//
//    //    // add the sprite as a child to this layer
//    //    this->addChild(sprite, 0);
//    //}
//
//    //// 创建一个空的动画对象
//    //auto animation = Animation::create();
//
//    //// 添加动画帧
//    //for (int i = 1; i <= 2; i++) {
//    //    char filename[100];
//    //    sprintf(filename, "pic%d.png", i);
//    //    auto frame = SpriteFrame::create(filename, Rect(0, 0, 70, 70));
//    //    animation->addSpriteFrame(frame);
//    //}
//
//    //// 设置动画属性
//    //animation->setDelayPerUnit(0.08f);
//    //animation->setLoops(-1);
//
//    //// 创建动画动作对象
//    //auto animate = Animate::create(animation);
//
//    //// 将动画动作应用到精灵对象上
//    //sprite->runAction(animate);
//
//
//    return true;
//}
//
//void HelloWorld::menuCloseCallback(Ref* pSender)
//{
//    //这个函数会停止游戏循环，并释放所有的资源。
//    Director::getInstance()->end();
//
//    //如果希望在iOS中返回原生界面而不是退出应用程序，可以注释掉这个函数，并调用下面的代码，
//    //触发一个名为“game_scene_close_event”的自定义事件，由RootViewController.mm文件中的代码处理。
//
//    //EventCustom customEndEvent("game_scene_close_event");
//    //_eventDispatcher->dispatchEvent(&customEndEvent);
//}
//
//void HelloWorld::onButtonClick(cocos2d::Ref* sender)
//{
//    // 在当前位置创建炮塔的逻辑代码
//    auto button = dynamic_cast<cocos2d::ui::Button*>(sender);
//    if (button)
//    {
//        auto tower = TestTower::create();  // 创建炮塔对象
//        tower->setPosition(button->getParent()->getPosition());  // 设置炮塔位置
//        auto thisTowerPosition = dynamic_cast<TowerPosition*> (button->getParent());
//        if (thisTowerPosition)
//        {
//            thisTowerPosition->towerofThisPosition = tower;
//        }
//        this->addChild(tower, 3);  // 将炮塔添加到场景中
//        button->getParent()->setVisible(false);
//    }
//}