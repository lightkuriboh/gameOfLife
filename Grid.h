//
// Created by kuribohkute on 20/06/2018.
//

#ifndef TEMPLATECPP_GRID_H
#define TEMPLATECPP_GRID_H

#include "cocos2d.h"
#include "Creature.h"

class Grid : public cocos2d::Sprite {
    public:
        CREATE_FUNC(Grid);
        bool init() override ;
        void evolveStep();
        int getGenerationCount();
        int getPopulationCount();

    protected:
        int generationCount;
        int populationCount;
        float ceilWidth;
        float ceilHeight;
        cocos2d::Vector<Creature*> gridArray;

        void setupGrid();
        void setupTouchHandling();
        void updateNeighborCount();
        void updateCreature();
        Creature* creatureForTouchLocation(cocos2d::Vec2 touchLocation);
        bool isValidIndex(int row, int col);
        int indexForRowColumn(int row, int col);
};

#endif //TEMPLATECPP_GRID_H
