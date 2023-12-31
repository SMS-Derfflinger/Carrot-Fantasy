#include "TowerBase.h"

// Tower函数实现
bool Tower::init() {
    if (!Sprite::init()) {
        return false;
    }

    return true;
}

int Tower::getConsumption() const
{
    return consumption;
}

float Tower::getRange() const {
    return range;
}

void Tower::setRange(float range) {
    this->range = range;
}

int Tower::getDamage() const {
    return damage;
}

void Tower::setDamage(int damage) {
    this->damage = damage;
}

Target* Tower::getTarget() const {
    return target;
}

void Tower::setTarget(Target* target) {
    this->target = target;
}

float Tower::getAttackDuration() {
    return attackDuration;
}

float Tower::getAttackInterval() const {
    return attackInterval;
}

void Tower::setAttackInterval(float attackInterval) {
    this->attackInterval = attackInterval;
}


// bottleTower函数实现
bool BottleTower::init() {
    if (!Sprite::init()) {
        return false;
    }

    return true;
}

void BottleTower::update(float delta) {
    // 更新冷却计时器
    cooldownTimer -= delta;

    if (cooldownTimer <= 0) {
        // 冷却结束，进行攻击
        cooldownTimer = 0.0f;
        attack();
    }
}

void BottleTower::attack() {
    // 判断是否在射程内
    float thisdistance = 0;
    if (target && target->isAlive()) {
        thisdistance = getPosition().distance(target->getPosition());
    }

    if (target && target->isAlive() && thisdistance + target->getRadius() <= getRange()) {
        // 继续攻击此目标
    }
    else {
        // 更换敌人
        // 选择射程内距离炮塔最近的敌人
        Vector<Node*> enemies = getScene()->getChildren();
        Target* nearestEnemy = nullptr;
        float minDistance = 999999;
        for (auto node : enemies) {
            auto enemy = dynamic_cast<Monster*>(node);
            if (enemy && enemy->isAlive()) {
                float distance = getPosition().distance(enemy->getPosition());
                if (enemy->isAlive() && distance + enemy->getRadius() <= getRange() && distance < minDistance) {
                    nearestEnemy = enemy;
                    minDistance = distance;
                }
            }
        }
        // 如果有敌人在射程，重新设置目标
        if (nearestEnemy) {
            setTarget(nearestEnemy);
        }
        else {
            setTarget(nullptr);
        }
    }

    // 如果有正确的目标，攻击
    if (target && target->isAlive()) {
        auto seq = Sequence::create(
            CallFunc::create([this]() {
                if (target && target->isAlive()) {
                    // 一次只能执行一个攻击动作
                    cooldownTimer = 99999;
                    // 播放攻击动画
                    playAttackAnimation();
                    // 攻击敌人
                    attackTarget();
                }
                }),
            nullptr
        );
        this->runAction(seq);
    }
}

void BottleTower::playAttackAnimation() {
    // 创建炮塔旋转动作
    // 获取炮塔当前位置和方向
    cocos2d::Vec2 towerPosition = getPosition();
    float towerAngle = this->getRotation();
    // 计算目标方向向量
    cocos2d::Vec2 direction = this->target->getPosition() - towerPosition;
    // 计算目标角度
    float targetAngle = -CC_RADIANS_TO_DEGREES(direction.getAngle()) + 90;
    // 计算旋转时间
    float rotate = targetAngle - towerAngle;
    while (rotate > 180) {
        rotate -= 360;
    }
    while (rotate < -180) {
        rotate += 360;
    }
    float rotateTime = abs(rotate / rotateSpeed);

    // 设置开火时间
    attackDuration = rotateTime + 0.075f;

    // 创建一个 RotateTo 动作，将炮塔旋转到目标角度
    auto rotateAction = RotateTo::create(rotateTime, targetAngle);

    // 用缩放模拟开火动画
    // 创建一个 ScaleTo 动作，将精灵在 0.1 秒内在 X 方向上缩放到 0.8 倍
    auto scaleXOut = ScaleTo::create(0.1f, 1.0f, 0.8f);
    // 创建一个 ScaleTo 动作，将精灵在 0.1 秒内在 X 方向上恢复到原始大小
    auto scaleXIn = ScaleTo::create(0.1f, 1.0f, 1.0f);

    // 重置冷却计时器
    auto callbackAction = CallFunc::create([=]() {
        cooldownTimer = attackInterval;
        });

    // 在攻击动画中运行旋转动作和开火动画
    auto sequenceAction = Sequence::create(rotateAction, scaleXOut, scaleXIn, callbackAction, nullptr);
    runAction(sequenceAction);

}

void BottleTower::attackTarget() {
    // 获取目标位置
    Target* thisTarget = this->target;
    cocos2d::Vec2 targetPosition = thisTarget->getPosition();
    // 获取炮塔当前位置
    cocos2d::Vec2 towerPosition = getPosition();
    // 创建炮弹精灵
    auto bullet = Sprite::create(Bullet);
    bullet->setPosition(towerPosition);
    this->getParent()->addChild(bullet,2);
    bullet->setVisible(false);

    // 子弹动作
    auto bulletAction = CallFunc::create([=]() {
        // 创建子弹旋转动作
        // 计算目标方向向量
        cocos2d::Vec2 direction = this->target->getPosition() - towerPosition;
        // 计算目标角度
        float targetAngle = -CC_RADIANS_TO_DEGREES(direction.getAngle()) + 90;
        // 旋转动作
        auto rotateAction = RotateTo::create(0, targetAngle);
        // 创建一个向目标移动的动作
        float distance = targetPosition.distance(towerPosition);
        float duration = distance / 2000; //子弹的速度
        auto moveAction = MoveTo::create(duration, targetPosition);
        // 执行动作
        bullet->setVisible(true);
        bullet->runAction(
            Sequence::create(
                rotateAction,
                moveAction,
                // 创建一个回调动作，在目标位置触发炮弹爆炸效果     
                CallFunc::create([=]() {
                    if (thisTarget && thisTarget->isAlive()) {
                        // 在目标位置创建爆炸效果
                        auto explosion = Sprite::create(Explosion);
                        explosion->setPosition(thisTarget->getPosition());
                        this->getParent()->addChild(explosion);
                        explosion->runAction(Sequence::create(
                            DelayTime::create(0.1f),
                            FadeOut::create(0.1f),// 淡出
                            RemoveSelf::create(),
                            nullptr
                        ));
                        // 产生伤害
                        thisTarget->takeDamage(getDamage());
                    }
                    // 移除炮弹精灵
                    this->getParent()->removeChild(bullet, true);
                    }),
                nullptr));
        });

    // 运行动作
    bullet->runAction(
        Sequence::create(
            DelayTime::create(attackDuration),
            bulletAction,
            nullptr)
    );
}



// sunTower函数实现
bool SunflowerTower::init() {
    if (!Sprite::init()) {
        return false;
    }

    return true;
}

void SunflowerTower::update(float delta) {
    // 更新冷却计时器
    cooldownTimer -= delta;

    if (cooldownTimer <= 0) {
        // 冷却结束，进行攻击
        cooldownTimer = 0.0f;
        attack();
    }
}

void SunflowerTower::attack() {
    // 判断是否在射程内
    float thisdistance = 0;
    if (target && target->isAlive()) {
        thisdistance = getPosition().distance(target->getPosition());
    }

    if (target && target->isAlive() && thisdistance + target->getRadius() <= getRange()) {
        // 继续攻击此目标
    }
    else {
        // 更换敌人
        // 选择射程内距离炮塔最近的敌人
        Vector<Node*> enemies = getScene()->getChildren();
        Target* nearestEnemy = nullptr;
        float minDistance = 999999;
        for (auto node : enemies) {
            auto enemy = dynamic_cast<Monster*>(node);
            if (enemy && enemy->isAlive()) {
                float distance = getPosition().distance(enemy->getPosition());
                if (enemy->isAlive() && distance + enemy->getRadius() <= getRange() && distance < minDistance) {
                    nearestEnemy = enemy;
                    minDistance = distance;
                }
            }
        }
        // 如果有敌人在射程，重新设置目标
        if (nearestEnemy) {
            setTarget(nearestEnemy);
        }
        else {
            setTarget(nullptr);
        }
    }

    // 如果有正确的目标，攻击
    if (target && target->isAlive()) {
        auto seq = Sequence::create(
            CallFunc::create([this]() {
                if (getTarget()) {
                    // 一次只能执行一个攻击动作
                    cooldownTimer = 99999;
                    // 播放攻击动画
                    playAttackAnimation();
                    // 攻击敌人
                    attackTarget();
                }
                }),
            nullptr
        );
        this->runAction(seq);
    }
}

void SunflowerTower::playAttackAnimation() {
    // 创建炮弹精灵
    auto bullet = Sprite::create(Bullet);
    bullet->setPosition(this->getPosition());
    this->getParent()->addChild(bullet);
    auto setCooldownTimer = CallFunc::create([=]() { cooldownTimer = attackInterval; });
    // 太阳特效
    bullet->runAction(
        Sequence::create(
            ScaleTo::create(0.15f, 3.0f, 3.0f),// 扩大
            FadeOut::create(0.05f),// 淡出
            RemoveSelf::create(),// 移除炮弹精灵
            setCooldownTimer,
            nullptr)
    );
}

void SunflowerTower::attackTarget() {
    // 攻击射程内所有的目标
    Vector<Node*> enemies = getScene()->getChildren();
    for (auto node : enemies) {
        auto enemy = dynamic_cast<Target*>(node);
        if (enemy && enemy->isAlive()) {
            float distance = getPosition().distance(enemy->getPosition());
            if (distance + enemy->getRadius() <= getRange()) {
                enemy->takeDamage(getDamage());
                // 在目标位置创建爆炸效果
                auto explosion = Sprite::create(Explosion);
                explosion->setPosition(enemy->getPosition());
                this->getParent()->addChild(explosion);
                explosion->runAction(Sequence::create(
                    DelayTime::create(0.1f),
                    FadeOut::create(0.1f),// 淡出
                    RemoveSelf::create(),
                    nullptr
                ));
            }
        }
    }
}



// starTower函数实现
bool StarTower::init() {
    if (!Sprite::init()) {
        return false;
    }

    return true;
}

void StarTower::update(float delta) {
    // 更新冷却计时器
    cooldownTimer -= delta;

    if (cooldownTimer <= 0) {
        // 冷却结束，进行攻击
        cooldownTimer = 0.0f;
        attack();
    }
}

void StarTower::attack() {
    // 判断是否在射程内
    float thisdistance = 0;
    if (target && target->isAlive()) {
        thisdistance = getPosition().distance(target->getPosition());
    }

    if (target && target->isAlive() && thisdistance + target->getRadius() <= getRange()) {
        // 继续攻击此目标
    }
    else {
        // 更换敌人
        // 选择射程内距离炮塔最近的敌人
        Vector<Node*> enemies = getScene()->getChildren();
        Target* nearestEnemy = nullptr;
        float minDistance = 999999;
        for (auto node : enemies) {
            auto enemy = dynamic_cast<Monster*>(node);
            if (enemy && enemy->isAlive()) {
                float distance = getPosition().distance(enemy->getPosition());
                if (enemy->isAlive() && distance + enemy->getRadius() <= getRange() && distance < minDistance) {
                    nearestEnemy = enemy;
                    minDistance = distance;
                }
            }
        }
        // 如果有敌人在射程，重新设置目标
        if (nearestEnemy) {
            setTarget(nearestEnemy);
        }
        else {
            setTarget(nullptr);
        }
    }

    // 如果有正确的目标，攻击
    if (target && target->isAlive()) {
        auto seq = Sequence::create(
            CallFunc::create([this]() {
                if (getTarget()) {
                    // 一次只能执行一个攻击动作
                    cooldownTimer = 99999;
                    // 播放攻击动画
                    playAttackAnimation();
                    // 攻击敌人
                    attackTarget();
                }
                }),
            nullptr
        );
        this->runAction(seq);
    }
}

void StarTower::playAttackAnimation() {
    cooldownTimer = attackInterval;
    // 没有开火动画
}

void StarTower::attackTarget() {
    // 获取目标位置
    Target* thisTarget = this->target;
    cocos2d::Vec2 targetPosition = thisTarget->getPosition();
    // 获取炮塔当前位置和方向
    cocos2d::Vec2 towerPosition = getPosition();
    // 创建炮弹精灵
    auto bullet = Sprite::create(Bullet);
    bullet->setPosition(towerPosition);
    this->getParent()->addChild(bullet, 2);
    bullet->setVisible(false);

    // 子弹动作
    auto bulletAction = CallFunc::create([=]() {
        // 创建一个向目标移动的动作
        float distance = targetPosition.distance(towerPosition);
        float duration = distance / 1000; //子弹的速度
        auto moveAction = MoveTo::create(duration, targetPosition);
        // 执行动作
        bullet->setVisible(true);
        bullet->runAction(
            Sequence::create(
                moveAction,
                // 创建一个回调动作，在目标位置触发炮弹爆炸效果
                CallFunc::create([=]() {
                    if (thisTarget && thisTarget->isAlive()) {
                        // 在目标位置创建爆炸效果
                        auto explosion = Sprite::create(Explosion);
                        explosion->setPosition(thisTarget->getPosition());
                        this->getParent()->addChild(explosion);
                        explosion->runAction(Sequence::create(
                            ScaleTo::create(0.1f, 1.5f, 1.5f),// 扩大
                            FadeOut::create(0.05f),// 淡出
                            RemoveSelf::create(),// 移除炮弹精灵
                            nullptr
                        ));
                        // 对目标产生伤害
                        thisTarget->takeDamage(getDamage() * 0.5);
                        // 溅射伤害
                        Vector<Node*> enemies = getScene()->getChildren();
                        for (auto node : enemies) {
                            auto enemy = dynamic_cast<Target*>(node);
                            if (enemy && enemy->isAlive()) {
                                float distance = getPosition().distance(enemy->getPosition());
                                if (distance + enemy->getRadius() <= bulletRange) {
                                    enemy->takeDamage(getDamage() * 0.5);
                                }
                            }
                        }
                    }
                    // 移除炮弹精灵
                    this->getParent()->removeChild(bullet, true);
                    }),
                nullptr));
        });

    // 运行动作
    bullet->runAction(
        Sequence::create(
            bulletAction,
            nullptr)
    );
}
