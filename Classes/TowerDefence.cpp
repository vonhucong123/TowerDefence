﻿/****************************************************************************
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

#include "startGame.h"
#include "TowerDefence.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;

Scene* TowerDefence::createScene()
{
    auto scene = Scene::create();
    auto layer = TowerDefence::create();
    scene->addChild(layer);
    return scene;
}

static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

bool TowerDefence::init()
{
    if (!Layer::init())
    {
        return false;
    }

    auto visibleSize = Director::getInstance()->getVisibleSize();

    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    

    auto background = Sprite::create("mainBackground/startGame.jpg");
    background->setPosition(visibleSize.width / 2, visibleSize.height / 2);
    this->addChild(background);
    
    this->scheduleOnce(schedule_selector(TowerDefence::goToStartGame, this), 1);
  
    return true;
}

void TowerDefence::menuCloseCallback(Ref* pSender)
{
    Director::getInstance()->end();
}

void TowerDefence::goToStartGame(float dt)
{
    auto playLayer = startGame::createScene();
    Director::getInstance()->replaceScene(TransitionFade::create(0.1f, playLayer));
}
