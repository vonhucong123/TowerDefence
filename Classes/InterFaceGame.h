#ifndef __INTERFACE_SCENE_H__
#define __INTERFACE_SCENE_H__

#include "cocos2d.h"
#include "Army.h"

class InterfaceGame : public cocos2d::Layer
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();

    void initAllButton();

    void gotoPlayLayer(cocos2d::Ref *sender, int _level);
    
    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);

    // implement the "static create()" method manually
    CREATE_FUNC(InterfaceGame);

};

#endif // 
