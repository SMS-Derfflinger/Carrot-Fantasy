#ifndef __OBSTACLE_H__
#define __OBSTACLE_H__

#include "ObstacleBase.h"

class TestObstacle : public Obstacle {
public:
    CREATE_FUNC(TestObstacle);

    virtual bool init() override;
};


#endif // __OBSTACLE_H__
