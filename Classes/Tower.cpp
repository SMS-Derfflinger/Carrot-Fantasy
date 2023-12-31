#include "Tower.h"
USING_NS_CC;

bool BottleTower_1::init() {
    if (!Sprite::init()) {
        return false;
    }

    //炮塔的图片
    this->initWithFile("BottleLevel1.png");
    // 子弹的图片
    Bullet = "BottleBullet.png";
    // 爆炸效果
    Explosion = "BottleBoom.png";
    // 设置射程、攻击力和攻击间隔
    range = 200;
    damage = 10;
    attackInterval = 1.0f;

    consumption = 100;
    rotateSpeed = 180;
    cooldownTimer = 0.0f;
    attackDuration = 0.0f;
    target = nullptr;
    // 创建定时器，定时更新炮塔状态
    scheduleUpdate();

    return true;
}

bool BottleTower_2::init() {
    if (!Sprite::init()) {
        return false;
    }

    //炮塔的图片
    this->initWithFile("BottleLevel2.png");
    // 子弹的图片
    Bullet = "BottleBullet.png";
    // 爆炸效果
    Explosion = "BottleBoom.png";
    // 设置射程、攻击力和攻击间隔
    range = 250;
    damage = 15;
    attackInterval = 1.0f;

    consumption = 150;
    rotateSpeed = 180;
    cooldownTimer = 0.0f;
    attackDuration = 0.0f;
    target = nullptr;
    // 创建定时器，定时更新炮塔状态
    scheduleUpdate();

    return true;
}

bool BottleTower_3::init() {
    if (!Sprite::init()) {
        return false;
    }

    //炮塔的图片
    this->initWithFile("BottleLevel3.png");
    // 子弹的图片
    Bullet = "BottleBullet.png";
    // 爆炸效果
    Explosion = "BottleBoom.png";
    // 设置射程、攻击力和攻击间隔
    range = 300;
    damage = 20;
    attackInterval = 1.0f;

    consumption = 250;
    rotateSpeed = 180;
    cooldownTimer = 0.0f;
    attackDuration = 0.0f;
    target = nullptr;
    // 创建定时器，定时更新炮塔状态
    scheduleUpdate();

    return true;
}

bool SunflowerTower_1::init() {
    if (!Sprite::init()) {
        return false;
    }

    //炮塔的图片
    this->initWithFile("SunflowerLevel1.png");
    // 子弹的图片
    Bullet = "SunflowerBullet.png";
    // 爆炸效果
    Explosion = "BottleBoom.png";
    // 设置射程、攻击力和攻击间隔
    range = 250;
    damage = 10;
    attackInterval = 1.0f;

    consumption = 200;
    cooldownTimer = 0.0f;
    attackDuration = 0.0f;
    target = nullptr;
    // 创建定时器，定时更新炮塔状态
    scheduleUpdate();

    return true;
}

bool SunflowerTower_2::init() {
    if (!Sprite::init()) {
        return false;
    }

    //炮塔的图片
    this->initWithFile("SunflowerLevel2.png");
    // 子弹的图片
    Bullet = "SunflowerBullet.png";
    // 爆炸效果
    Explosion = "BottleBoom.png";
    // 设置射程、攻击力和攻击间隔
    range = 250;
    damage = 15;
    attackInterval = 1.0f;

    consumption = 200;
    cooldownTimer = 0.0f;
    attackDuration = 0.0f;
    target = nullptr;
    // 创建定时器，定时更新炮塔状态
    scheduleUpdate();

    return true;
}

bool SunflowerTower_3::init() {
    if (!Sprite::init()) {
        return false;
    }

    //炮塔的图片
    this->initWithFile("SunflowerLevel3.png");
    // 子弹的图片
    Bullet = "SunflowerBullet.png";
    // 爆炸效果
    Explosion = "BottleBoom.png";
    // 设置射程、攻击力和攻击间隔
    range = 250;
    damage = 25;
    attackInterval = 1.0f;

    consumption = 200;
    cooldownTimer = 0.0f;
    attackDuration = 0.0f;
    target = nullptr;
    // 创建定时器，定时更新炮塔状态
    scheduleUpdate();

    return true;
}

bool StarTower_1::init() {
    if (!Sprite::init()) {
        return false;
    }

    //炮塔的图片
    this->initWithFile("StarLevel1.png");
    // 子弹的图片
    Bullet = "StarBulletLevel1.png";
    // 爆炸效果
    Explosion = "StarBoom.png";
    // 设置射程、攻击力和攻击间隔
    range = 200;
    damage = 15;
    attackInterval = 1.0f;

    consumption = 200;
    bulletRange = 500;
    cooldownTimer = 0.0f;
    attackDuration = 0.0f;
    target = nullptr;
    // 创建定时器，定时更新炮塔状态
    scheduleUpdate();

    return true;
}

bool StarTower_2::init() {
    if (!Sprite::init()) {
        return false;
    }

    //炮塔的图片
    this->initWithFile("StarLevel2.png");
    // 子弹的图片
    Bullet = "StarBulletLevel2.png";
    // 爆炸效果
    Explosion = "StarBoom.png";
    // 设置射程、攻击力和攻击间隔
    range = 250;
    damage = 20;
    attackInterval = 1.0f;

    consumption = 200;
    bulletRange = 500;
    cooldownTimer = 0.0f;
    attackDuration = 0.0f;
    target = nullptr;
    // 创建定时器，定时更新炮塔状态
    scheduleUpdate();

    return true;
}

bool StarTower_3::init() {
    if (!Sprite::init()) {
        return false;
    }

    //炮塔的图片
    this->initWithFile("StarLevel3.png");
    // 子弹的图片
    Bullet = "StarBulletLevel3.png";
    // 爆炸效果
    Explosion = "StarBoom.png";
    // 设置射程、攻击力和攻击间隔
    range = 300;
    damage = 25;
    attackInterval = 1.0f;

    consumption = 200;
    bulletRange = 500;
    cooldownTimer = 0.0f;
    attackDuration = 0.0f;
    target = nullptr;
    // 创建定时器，定时更新炮塔状态
    scheduleUpdate();

    return true;
}