#ifndef __START_GAME_SCENE_H__
#define __START_GAME_SCENE_H__

#include "cocos2d.h"
#include "Data.h"

class startGame : public cocos2d::Layer
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();
    
    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);

    void initSetting();

    void initRegistration();

    void initLogin();

    void soundSetting();

    void musicSetting();

    void goToInterfaceGame();

    // implement the "static create()" method manually
    CREATE_FUNC(startGame);

    GameData m_userData;

};

#endif // __START_GAME_SCENE_H__
