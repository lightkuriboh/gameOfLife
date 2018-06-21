//
// Created by kuribohkute on 17/06/2018.
//

#ifndef TEMPLATECPP_HELLOWORLD_H
#define TEMPLATECPP_HELLOWORLD_H

#include "cocos2d.h"

class Creature : public cocos2d :: Sprite {
    public:
        CREATE_FUNC(Creature);
        bool init() override;
        void setLivingNeighborsCount(int livingNeighborsCount);
        int getLivingNeighbor();
        void setIsAlive(bool isAlive);
        bool getIsAlive();

    protected:
        int livingNeighborsCount;
        bool isAlive;
};

#endif //TEMPLATECPP_HELLOWORLD_H
