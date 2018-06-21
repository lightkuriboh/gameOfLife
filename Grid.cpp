//
// Created by kuribohkute on 20/06/2018.
//

#include "Grid.h"
#include <random>

const int ROWS = 50;
const int COLUMNS = 50;

using namespace cocos2d;

#include <iostream>
using namespace std;

bool Grid::init() {

    if ( !Sprite::initWithFile("../Resources/grid.jpg") ) {
        return false;
    }

    generationCount = 0;
    populationCount = 0;

    this->setupGrid();
    this->setupTouchHandling();

    return true;
}

void Grid::setupGrid() {

    srand((unsigned int)time(nullptr));

    this->setAnchorPoint(Vec2(0, 0));

    float w = this->getContentSize().width,
        h = this->getContentSize().height;
    this->setScale(640 / w, 640 / h);

    ceilWidth = 640 / COLUMNS;
    ceilHeight = 640 / ROWS;

    gridArray.reserve(ROWS * COLUMNS);

    for (int row = 0; row < ROWS; row++) {
        for (int col = 0; col < COLUMNS; col++) {
            Creature* creature = Creature::create();

            creature->setAnchorPoint(Vec2(0, 0));
            creature->setPosition(Vec2(ceilWidth * col, ceilHeight * row));

            creature->setContentSize(Size(ceilWidth, ceilHeight));

            if (rand() % 2){
                creature->setIsAlive(true);
            } else {
                creature->setIsAlive(false);
            }

            this->addChild(creature);

            gridArray.pushBack(creature);
        }
    }
}

int Grid::getPopulationCount() {
    return this->populationCount;
}

int Grid::getGenerationCount() {
    return this->generationCount;
}

void Grid::setupTouchHandling() {
    auto touchListener = EventListenerTouchOneByOne::create();
    touchListener->onTouchBegan = [&](Touch* touch, Event* event) {
        Vec2 gridTouchLocation = this->convertTouchToNodeSpace(touch);
        Creature* touchedCreature = this->creatureForTouchLocation(gridTouchLocation);
        if (touchedCreature) {
            touchedCreature->setIsAlive(!touchedCreature->getIsAlive());
            cout << "touched\n";
        }
        return true;
    };
    this->getEventDispatcher()->addEventListenerWithFixedPriority(touchListener, 1);
}

Creature* Grid::creatureForTouchLocation(cocos2d::Vec2 touchLocation) {

    auto X = touchLocation.x;
    auto Y = touchLocation.y;

    if (X < 0.0f && Y < 0.0f) {
        return nullptr;
    }

    int row = int(Y / ceilHeight),
        col = int(X / ceilWidth);

    if (this->isValidIndex(row, col)) {
        return gridArray.at(this->indexForRowColumn(row, col));
    }

    return nullptr;
}

bool Grid::isValidIndex(int row, int col) {
    row += ROWS;
    col += COLUMNS;
    row %= ROWS;
    col %= COLUMNS;
    return (row >= 0 && row < ROWS) && (col >= 0 && col < COLUMNS);
}

int Grid::indexForRowColumn(int row, int col) {
    row += ROWS;
    col += COLUMNS;
    row %= ROWS;
    col %= COLUMNS;
    return row * COLUMNS + col;
}

void Grid::evolveStep() {
    this->updateNeighborCount();
    this->updateCreature();
    this->generationCount++;
}

void Grid::updateNeighborCount() {
    for (int row = 0; row < ROWS; row++) {
        for (int col = 0; col < COLUMNS; col++) {
            int currentIndex = this->indexForRowColumn(row, col);

            Creature* creature = gridArray.at(currentIndex);

            creature->setLivingNeighborsCount(0);

            for (int nRow = row - 1; nRow <= row + 1; nRow++) {
                for (int nCol = col - 1; nCol <= col + 1; nCol++) {

                    bool valid = this->isValidIndex(nRow, nCol);

                    if (valid && !(row == nRow && col == nCol)) {
                        int nIndex = this->indexForRowColumn(nRow, nCol);
                        Creature* nCreature = gridArray.at(nIndex);

                        if (nCreature->getIsAlive()) {

                            int currentLiving = creature->getLivingNeighbor();

                            creature->setLivingNeighborsCount(currentLiving + 1);
                        }
                    }

                }
            }

        }
    }
}

void Grid::updateCreature() {

    this->populationCount = 0;
    for (int row = 0; row < ROWS; row++) {
        for (int col = 0; col < COLUMNS; col++) {
            int index = this->indexForRowColumn(row, col);
            Creature* creature = gridArray.at(index);

            if (creature->getIsAlive()) {
                if (creature->getLivingNeighbor() != 2 && creature->getLivingNeighbor() != 3) {
                    creature->setIsAlive(false);
                }
            } else {
                if (creature->getLivingNeighbor() == 3) {
                    creature->setIsAlive(true);
                }
            }

            if (creature->getIsAlive()) {
                this->populationCount++;
            }
        }
    }

}
