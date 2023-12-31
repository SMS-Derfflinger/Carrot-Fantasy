#include "Target.h"
#include "SceneBase.h"
#include "Tower.h"

USING_NS_CC;


void Target::setAllTarget() {
    Vector<Node*> enemies = getScene()->getChildren();
    Target* nearestEnemy = nullptr;
    float minDistance = 999999;
    for (auto node : enemies) {
        auto tower = dynamic_cast<Tower*>(node);
        if (tower) {
            tower->setTarget(this);
        }
    }
}

void Target::takeDamage(int damage) {
    HP -= damage;
    if (HP <= 0) {
        auto scene = dynamic_cast<SceneBase*>(this->getParent());
        if (scene)
        {
            scene->updateMoney(value);
        }
        // 播放死亡动画、移除目标
        this->runAction(Sequence::create(
            FadeOut::create(0.25f),// 淡出
            RemoveSelf::create(),
            nullptr
        ));
    }
    if (!Progress) {
        // 创建一个进度条精灵
        auto progress = cocos2d::ProgressTimer::create(cocos2d::Sprite::create("ProgressAfter.png"));
        Sprite* progressBackground = Sprite::create("ProgressInit.png");
        progress->setType(cocos2d::ProgressTimer::Type::BAR);
        progress->setMidpoint(cocos2d::Vec2(0, 0.5));  // 设置进度条起点为左边中间位置
        progress->setBarChangeRate(cocos2d::Vec2(1, 0));  // 设置进度条的宽度随百分比变化

        // 将进度条精灵添加到怪物头顶上
        this->addChild(progressBackground);
        this->addChild(progress);
        progress->setPosition(cocos2d::Vec2(this->getContentSize().width / 2, this->getContentSize().height));
        progressBackground->setPosition(cocos2d::Vec2(this->getContentSize().width / 2, this->getContentSize().height));
        this->Progress = progress;
    }
    if (HP < maxHP&& Progress) {
        // 设置进度条的百分比
        float percent = static_cast<float>(HP * 100 / maxHP);
        this->Progress->setPercentage(percent);
    }
}

bool Target::isAlive() const {
    return HP > 0;
}

void Target::setHP(int HP) {
    this->HP = HP;
    if (HP <= 0) {
        // 播放死亡动画、移除目标
        this->runAction(Sequence::create(
            FadeOut::create(0.25f),// 淡出
            RemoveSelf::create(),
            nullptr
        ));

    }
}

int Target::getRadius() {
    return radius;
}