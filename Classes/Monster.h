#ifndef __MONSTER_H__
#define __MONSTER_H__

#include "MonsterBase.h"

class Rabbit : public Monster {
public:
    CREATE_FUNC(Rabbit);

    virtual void moveToSequence(const std::vector<cocos2d::Vec2>& positions) override;
    virtual bool init() override;

};


class FlyingRabbit : public Monster {
public:
    CREATE_FUNC(FlyingRabbit);

    virtual void moveToSequence(const std::vector<cocos2d::Vec2>& positions) override;
    virtual bool init() override;

};

class FastrRabbit : public Monster {
public:
    CREATE_FUNC(FastrRabbit);

    virtual void moveToSequence(const std::vector<cocos2d::Vec2>& positions) override;
    virtual bool init() override;

};
#endif // __MONSTER_H__