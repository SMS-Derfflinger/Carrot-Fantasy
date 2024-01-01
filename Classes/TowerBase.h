#ifndef __TOWERBASE_H__
#define __TOWERBASE_H__

#include "Target.h"
#include "MonsterBase.h"
#include "SceneMain.h"

USING_NS_CC;

class TowerPosition;

class Tower : public cocos2d::Sprite {
public:
    // 初始化函数
    virtual bool init() override;
    // 建造花费
    int getConsumption() const;
    // 射程
    float getRange() const;
    // 修改射程
    void setRange(float range);
    // 攻击力
    int getDamage() const;
    // 修改攻击力
    void setDamage(int damage);
    // 目标
    Target* getTarget() const;
    // 修改目标
    void setTarget(Target* target);
    // 炮塔攻击动画的时长
    float getAttackDuration();
    // 攻击间隔
    float getAttackInterval() const;
    // 修改攻击间隔
    void setAttackInterval(float attackInterval);

    // 播放炮塔的攻击动画
    virtual void playAttackAnimation() = 0;
    // 执行攻击逻辑
    virtual void attack() = 0;

    // 点击逻辑
    virtual void clicked(int &sceneMoney) = 0;

    Sprite* bottom = nullptr;
    TowerPosition* thisTowerPositionIS =nullptr;



protected:
    // 建造花费
    int consumption;
    // 射程
    float range;
    // 攻击力
    int damage;
    // 目标
    Target* target;
    // 炮塔攻击动画的时长
    float attackDuration;
    // 攻击间隔
    float attackInterval;
    // 冷却计时器
    float cooldownTimer;
};

// 瓶子塔
class BottleTower : public Tower {
public:
    // 初始化函数
    virtual bool init() override;
  //  CREATE_FUNC(BottleTower);
    // 在主循环运行的更新函数
    void update(float delta);

    // 播放炮塔的攻击动画
    void playAttackAnimation() override;
    // 执行攻击逻辑
    void attack() override;
    // 发射子弹
    void attackTarget();
protected:
    // 旋转速度
    float rotateSpeed;
    // 子弹的图片
    std::string Bullet;
    // 爆炸效果
    std::string Explosion;
};

// 太阳塔
class SunflowerTower : public Tower {
public:
    // 初始化函数
    virtual bool init() override;
  //  CREATE_FUNC(SunflowerTower);
    // 在主循环运行的更新函数
    void update(float delta);

    // 播放炮塔的攻击动画
    void playAttackAnimation() override;
    // 执行攻击逻辑
    void attack() override;
    // 发射子弹
    void attackTarget();
protected:
    // 子弹的图片
    std::string Bullet;
    // 爆炸效果
    std::string Explosion;
};

// 星星塔
class StarTower : public Tower {
public:
    // 初始化函数
    virtual bool init() override;
   // CREATE_FUNC(StarTower);
    // 在主循环运行的更新函数
    void update(float delta);

    // 播放炮塔的攻击动画
    void playAttackAnimation() override;
    // 执行攻击逻辑
    void attack() override;
    // 发射子弹
    void attackTarget();
protected:
    // 爆炸范围
    float bulletRange;
    // 子弹的图片
    std::string Bullet;
    // 爆炸效果
    std::string Explosion;
};

#endif // __TOWERBASE_H__