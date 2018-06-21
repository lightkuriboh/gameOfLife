//
// Created by kuribohkute on 20/06/2018.
//

#ifndef TEMPLATECPP_GAMEMENU_H
#define TEMPLATECPP_GAMEMENU_H

#include "cocos2d.h"
#include "Grid.h"

class GameMenu : public cocos2d::Sprite {
    public:
        CREATE_FUNC(GameMenu);
        bool init() override ;
        void runGame();
        int getGeneration();
        int getPopulation();

    protected:
        Grid* grid;
        void initButton();
        void initLayout();
        int Width;
        int Height;
};

#endif //TEMPLATECPP_GAMEMENU_H
