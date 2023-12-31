#include "Monster.h"
#include "SceneBase.h"
USING_NS_CC;




bool Rabbit::init() {
    if (!Sprite::init()) {
        return false;
    }

    //// 初始化怪物的外观和属性
    //this->initWithFile("tuzi1.png");

    cocos2d::ui::Button* BUTTON = cocos2d::ui::Button::create("cat.png");
    BUTTON->setOpacity(0);
    BUTTON->addClickEventListener([this](Ref* sender) {
        // 处理按钮点击事件
        setAllTarget();
        });
    BUTTON->setPosition(Vec2(50, 50));
    addChild(BUTTON);

    // 初始化HP
    maxHP = HP = 100;
    // 初始化击杀奖励
    value = 50;
    // 初始化速度
    speed = 30;
    // 初始化半径
    radius = 10;

    return true;
}

void Rabbit::moveToSequence(const std::vector<cocos2d::Vec2>& positions)
{
    this->stopAllActions(); // 停止当前进行中的动作

    Vector<FiniteTimeAction*> actions; // 创建一个动作数组
    cocos2d::Vec2 thisPosition = this->getPosition();
    for (cocos2d::Vec2 position : positions)
    {
        auto distance = position - thisPosition; // 计算移动距离
        thisPosition = position;
        auto duration = distance.length() / speed; // 计算移动时间
        auto move = MoveTo::create(duration, position); // 创建移动动作
        actions.pushBack(move); // 将移动动作添加到数组中
    }

    auto attacked = CallFunc::create([=]() {
        auto target = this->getParent();
        auto scene = dynamic_cast<SceneBase*>(target);
        scene->takeCarrotDamage(1);
        this->setHP(0);

        });
    auto sequenceAction = Sequence::create(actions); // 创建序列动作
    auto sequence = Sequence::create(sequenceAction, attacked, nullptr);

    // 创建一个空的动画对象
    auto animation = Animation::create();
    // 添加动画帧
    for (int i = 8; i >= 1; i--) {
        char filename[100];
        sprintf(filename, "tuzi%d.png", i);
        auto frame = SpriteFrame::create(filename, Rect(0, 0, 100, 100));
        animation->addSpriteFrame(frame);
    }

    // 设置动画属性
    animation->setDelayPerUnit(0.08f);
    animation->setLoops(-1);

    // 创建动画动作对象
    auto animate = Animate::create(animation);

    // 将动画动作应用到精灵对象上
    this->runAction(Spawn::create(animate,sequence,nullptr)); // 执行序列动作
}

bool FlyingRabbit::init() {
    if (!Sprite::init()) {
        return false;
    }

    // 初始化怪物的外观和属性
    // 初始化HP
    maxHP = HP = 100;
    // 初始化击杀奖励
    value = 50;
    // 初始化速度
    speed = 30;
    // 初始化半径
    radius = 10;

    cocos2d::ui::Button* BUTTON = cocos2d::ui::Button::create("cat.png");
    BUTTON->setOpacity(0);
    BUTTON->addClickEventListener([this](Ref* sender) {
        // 处理按钮点击事件
        setAllTarget();
        });
    BUTTON->setPosition(Vec2(50, 50));
    addChild(BUTTON);

    return true;
}

void FlyingRabbit::moveToSequence(const std::vector<cocos2d::Vec2>& positions)
{
    this->stopAllActions(); // 停止当前进行中的动作

    Vector<FiniteTimeAction*> actions; // 创建一个动作数组
    cocos2d::Vec2 thisPosition = this->getPosition();
    for (cocos2d::Vec2 position : positions)
    {
        auto distance = position - thisPosition; // 计算移动距离
        thisPosition = position;
        auto duration = distance.length() / speed; // 计算移动时间
        auto move = MoveTo::create(duration, position); // 创建移动动作
        actions.pushBack(move); // 将移动动作添加到数组中
    }

    auto attacked = CallFunc::create([=]() {
        auto target = this->getParent();
        auto scene = dynamic_cast<SceneBase*>(target);
        scene->takeCarrotDamage(1);
        this->setHP(0);

        });
    auto sequenceAction = Sequence::create(actions); // 创建序列动作
    auto sequence = Sequence::create(sequenceAction, attacked, nullptr);

    // 创建一个空的动画对象
    auto animation = Animation::create();
    // 添加动画帧
    for (int i = 1; i <= 5; i++) {
        char filename[100];
        sprintf(filename, "fei%d.png", i);
        auto frame = SpriteFrame::create(filename, Rect(0, 0, 110, 110));
        animation->addSpriteFrame(frame);
    }

    // 设置动画属性
    animation->setDelayPerUnit(0.08f);
    animation->setLoops(-1);

    // 创建动画动作对象
    auto animate = Animate::create(animation);

    // 将动画动作应用到精灵对象上
    this->runAction(Spawn::create(animate, sequence, nullptr)); // 执行序列动作
}

bool FastrRabbit::init() {
    if (!Sprite::init()) {
        return false;
    }

    // 初始化怪物的外观和属性
    // 初始化HP
    maxHP = HP = 100;
    // 初始化击杀奖励
    value = 50;
    // 初始化速度
    speed = 50;
    // 初始化半径
    radius = 10;

    cocos2d::ui::Button* BUTTON = cocos2d::ui::Button::create("cat.png");
    BUTTON->setOpacity(0);
    BUTTON->addClickEventListener([this](Ref* sender) {
        // 处理按钮点击事件
        setAllTarget();
        });
    BUTTON->setPosition(Vec2(50, 50));
    addChild(BUTTON);

    return true;
}

void FastrRabbit::moveToSequence(const std::vector<cocos2d::Vec2>& positions)
{
    this->stopAllActions(); // 停止当前进行中的动作

    Vector<FiniteTimeAction*> actions; // 创建一个动作数组
    cocos2d::Vec2 thisPosition = this->getPosition();
    for (cocos2d::Vec2 position : positions)
    {
        auto distance = position - thisPosition; // 计算移动距离
        thisPosition = position;
        auto duration = distance.length() / speed; // 计算移动时间
        auto move = MoveTo::create(duration, position); // 创建移动动作
        actions.pushBack(move); // 将移动动作添加到数组中
    }

    auto attacked = CallFunc::create([=]() {
        auto target = this->getParent();
        auto scene = dynamic_cast<SceneBase*>(target);
        scene->takeCarrotDamage(1);
        this->setHP(0);

        });
    auto sequenceAction = Sequence::create(actions); // 创建序列动作
    auto sequence = Sequence::create(sequenceAction, attacked, nullptr);

    // 创建一个空的动画对象
    auto animation = Animation::create();
    // 添加动画帧
    for (int i = 1; i <= 2; i++) {
        char filename[100];
        sprintf(filename, "fastr%d.png", i);
        auto frame = SpriteFrame::create(filename, Rect(0, 0, 100, 100));
        animation->addSpriteFrame(frame);
    }

    // 设置动画属性
    animation->setDelayPerUnit(0.2f);
    animation->setLoops(-1);

    // 创建动画动作对象
    auto animate = Animate::create(animation);

    // 将动画动作应用到精灵对象上
    this->runAction(Spawn::create(animate, sequence, nullptr)); // 执行序列动作
}