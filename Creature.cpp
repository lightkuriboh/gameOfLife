//
// Created by kuribohkute on 17/06/2018.
//
#include "Creature.h"

USING_NS_CC;

using namespace cocos2d;

bool Creature::init() {
    if ( !Sprite::initWithFile("../Resources/bubble2.png") ) {
        return false;
    }
    this->setLivingNeighborsCount(0);
    this->setIsAlive(false);
    return true;
}

void Creature::setLivingNeighborsCount(int livingNeighborsCount) {
    this->livingNeighborsCount = livingNeighborsCount;
}

void Creature::setIsAlive(bool isAlive) {
    this->isAlive = isAlive;
    this->setVisible(isAlive);
}

int Creature::getLivingNeighbor() {
    return this->livingNeighborsCount;
}

bool Creature::getIsAlive() {
    return this->isAlive;
}

