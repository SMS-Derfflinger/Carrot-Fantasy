#ifndef __OBSTACLEBASE_H__
#define __OBSTACLEBASE_H__

#include "Target.h"

class Obstacle : public Target {
public:
    // 虚析构
    virtual ~Obstacle() {};

protected:
    Obstacle() {};// 受保护的构造函数
};

#endif // __OBSTACLEBASE_H__