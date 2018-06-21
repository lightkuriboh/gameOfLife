//
// Created by kuribohkute on 20/06/2018.
//
#include "GameMenu.h"
#include "Grid.h"
#include "ui/CocosGUI.h"

using namespace cocos2d;

bool GameMenu::init() {

    if ( !Sprite::initWithFile("../Resources/bg.jpg") ) {
        return false;
    }

    initButton();
    initLayout();

    this->setPosition(Vec2(0, 0));
    this->setAnchorPoint(Vec2(0, 0));
    this->setContentSize(Size(960, 640));

    return true;
}

void GameMenu::initButton() {

}

void GameMenu::initLayout() {
    (this->grid) = Grid::create();
    this->addChild(this->grid);

    (this->grid)->setPosition(Vec2(320, 0));
}

void GameMenu::runGame() {
    (this->grid)->evolveStep();
}

int GameMenu::getGeneration() {
    return (this->grid)->getGenerationCount();
}

int GameMenu::getPopulation() {
    return (this->grid)->getPopulationCount();
}