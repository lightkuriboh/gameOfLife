/****************************************************************************
 Copyright (c) 2017-2018 Xiamen Yaji Software Co., Ltd.
 
 http://www.cocos2d-x.org
 
 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:
 
 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.
 
 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
 ****************************************************************************/

#include "HelloWorldScene.h"
#include "SimpleAudioEngine.h"
#include "GameMenu.h"
#include "ui/CocosGUI.h"
#include <iostream>
using namespace std;

USING_NS_CC;

static int Width = 960;
static int Height = 640;

Scene* HelloWorld::createScene() {
    auto scene = Scene::create();
    auto layer = HelloWorld::create();
    scene->addChild(layer);
    return scene;
}

bool HelloWorld::init() {

    if ( !Scene::init() ) {
        return false;
    }


//    auto sprite = Sprite::create("../Resources/tree.png");
//    sprite->setAnchorPoint(Vec2(0, 0));
//    sprite->setPosition(0, 0);
//
//
//    auto moveTo1 = MoveTo::create(0.5, Vec2(0, 480));
//    auto moveTo2 = MoveTo::create(0.5, Vec2(480, 480));
//    auto moveTo3 = MoveTo::create(0.5, Vec2(480, 0));
//    auto moveTo4 = MoveTo::create(0.5, Vec2(0, 0));
//    auto fadeIn = FadeIn::create(0.5);
//    auto fadeOut = FadeOut::create(0.5);
//    auto bigger = ScaleBy::create(0.5, 2);
//    auto smaller = ScaleBy::create(0.5, 0.25);
//    auto rotateRight = RotateBy::create(0.5, 360);
//    auto rotateLeft = RotateBy::create(0.5, -360);
//    auto seq = Repeat::create(Sequence::create(bigger, smaller, rotateRight, rotateLeft, fadeOut, fadeIn,
//                                moveTo1, moveTo2, moveTo3, moveTo4,
//                                fadeOut, fadeIn, bigger, smaller, rotateRight, rotateLeft, nullptr), 3);
//    sprite->runAction(seq);


    this->myMenu = GameMenu::create();

    this->addChild(myMenu);

    this->initButton();

    return true;
}

void HelloWorld::play(Ref* pSender, cocos2d::ui::Widget::TouchEventType type) {
    this->schedule(CC_SCHEDULE_SELECTOR(HelloWorld::step), 0.1f);
}

void HelloWorld::pause(Ref* pSender, cocos2d::ui::Widget::TouchEventType type) {
    this->unschedule(CC_SCHEDULE_SELECTOR(HelloWorld::step));
}

void HelloWorld::step(float dt) {

    (this->myMenu)->runGame();

    genCount->setString(std::to_string(this->myMenu->getGeneration()));
    popCount->setString(std::to_string(this->myMenu->getPopulation()));
}

void HelloWorld::playWithoutButton() {
    this->schedule(CC_SCHEDULE_SELECTOR(HelloWorld::step), 0.05f);
}

void HelloWorld::initButton() {

    auto playButton = cocos2d::ui::Button::create("../Resources/rsz_play.png");
    playButton->addTouchEventListener(CC_CALLBACK_2(HelloWorld::play, this));
    playButton->setPosition(Vec2(Width * 0.025, Height * 0.75));
    playButton->setContentSize(Size(Width * 0.3, Height * 0.2));
    playButton->setAnchorPoint(Vec2(0, 0));
    this->myMenu->addChild(playButton);

    auto pauseButton = cocos2d::ui::Button::create("../Resources/rsz_pause.png");
    pauseButton->addTouchEventListener(CC_CALLBACK_2(HelloWorld::pause, this));
    pauseButton->setPosition(Vec2(Width * 0.025, Height * 0.50));
    pauseButton->setContentSize(Size(Width * 0.3, Height * 0.2));
    pauseButton->setAnchorPoint(Vec2(0, 0));
    this->myMenu->addChild(pauseButton);

    popCount = cocos2d::ui::Text::create("population", "fonts/LinLibertine_aBS.ttf", 32.f);
    popCount->setPosition(Vec2(20, 200));
    popCount->setAnchorPoint(Vec2(0, 0));
//    genCount->setColor(Color3B(255, 0, 0));
    genCount = cocos2d::ui::Text::create("generation", "fonts/LinLibertine_aBS.ttf", 32.f);
    genCount->setPosition(Vec2(20, 100));
    genCount->setAnchorPoint(Vec2(0, 0));
//    genCount->setColor(Color3B(255, 0, 0));

    this->myMenu->addChild(popCount);
    this->myMenu->addChild(genCount);



}
