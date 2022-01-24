#include "InterFaceGame.h"
#include "SimpleAudioEngine.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
#include "Army.h"
#include "PlayLayer.h"
USING_NS_CC;

Scene* InterfaceGame::createScene()
{
    auto scene = Scene::create();
    auto layer = InterfaceGame::create();
    scene->addChild(layer);
    return scene;
}

static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

bool InterfaceGame::init()
{
    if (!Layer::init())
    {
        return false;
    }

    auto visibleSize = Director::getInstance()->getVisibleSize();

    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
    auto mainMenu = CSLoader::getInstance()->createNode("csb/interfaceGame.csb");
    this->addChild(mainMenu);

    initAllButton();
    return true;
}

void InterfaceGame::initAllButton()
{
    auto buttonFire = utils::findChild<ui::Button*>(this, "Button_Fire");
    buttonFire->setTouchEnabled(true);
    buttonFire->addClickEventListener([=](Ref*)
        {
            
        });

    auto buttonSnow = utils::findChild<ui::Button*>(this, "Button_Snow");
    buttonSnow->setTouchEnabled(true);
    buttonSnow->addClickEventListener([=](Ref*)
        {

        });

    auto buttonElec = utils::findChild<ui::Button*>(this, "Button_Electric");
    buttonElec->setTouchEnabled(true);
    buttonElec->addClickEventListener([=](Ref*)
        {

        });

    auto buttonTime = utils::findChild<ui::Button*>(this, "Button_Time");
    buttonTime->setTouchEnabled(true);
    buttonTime->addClickEventListener([=](Ref*)
        {

        });

    auto buttonProtec = utils::findChild<ui::Button*>(this, "Button_Protec");
    buttonProtec->setTouchEnabled(true);
    buttonProtec->addClickEventListener([=](Ref*)
        {

        });

    auto buttonUpKata = utils::findChild<ui::Button*>(this, "Button_UpKatana");
    buttonUpKata->setTouchEnabled(true);
    buttonUpKata->addClickEventListener([=](Ref*)
        {

        });

    auto buttonRain = utils::findChild<ui::Button*>(this, "Button_Rain");
    buttonRain->setTouchEnabled(true);
    buttonRain->addClickEventListener([=](Ref*)
        {
            
        });

    auto buttonRainStone = utils::findChild<ui::Button*>(this, "Button_RainStone");
    buttonRainStone->setTouchEnabled(true);
    buttonRainStone->addClickEventListener([=](Ref*)
        {
           
        });

    auto buttonQuick = utils::findChild<ui::Button*>(this, "Button_Quick");
    buttonQuick->setTouchEnabled(true);
    buttonQuick->addClickEventListener([=](Ref*)
        {
            // load data here
            gotoPlayLayer(this, 1);
        });

    auto buttonStart = utils::findChild<ui::Button*>(this, "Button_Start");
    buttonStart->setTouchEnabled(true);
    buttonStart->addClickEventListener([=](Ref*)
        {
            auto levelTable = utils::findChild<ui::ImageView*>(this, "LevelTable");
            levelTable->setVisible(true);
           
        });

    auto button_closeLevel = utils::findChild<ui::Button*>(this, "Button_closeLevel");
    button_closeLevel->setTouchEnabled(true);
    button_closeLevel->addClickEventListener([=](Ref*)
        {
            auto levelTable = utils::findChild<ui::ImageView*>(this, "LevelTable");
            levelTable->setVisible(false);
        });

    auto buttonPause = utils::findChild<ui::Button*>(this, "Button_pause");
    buttonPause->setTouchEnabled(true);
    buttonPause->addClickEventListener([=](Ref*)
        {

        });

    // init button level
    auto buttonLevel1 = utils::findChild<ui::Button*>(this, "Button_level1");
    buttonLevel1->setTouchEnabled(true);
    buttonLevel1->addClickEventListener([=](Ref*)
        {
            gotoPlayLayer(this, 1);
        });
    auto buttonLevel2 = utils::findChild<ui::Button*>(this, "Button_level2");
    buttonLevel2->setTouchEnabled(true);
    buttonLevel2->addClickEventListener([=](Ref*)
        {
            gotoPlayLayer(this, 2);
        });

    auto buttonLevel3 = utils::findChild<ui::Button*>(this, "Button_level3");
    buttonLevel3->setTouchEnabled(true);
    buttonLevel3->addClickEventListener([=](Ref*)
        {
            gotoPlayLayer(this, 3);
        });

    auto buttonLevel4 = utils::findChild<ui::Button*>(this, "Button_level4");
    buttonLevel4->setTouchEnabled(true);
    buttonLevel4->addClickEventListener([=](Ref*)
        {
            gotoPlayLayer(this, 4);
        });

    auto buttonLevel5 = utils::findChild<ui::Button*>(this, "Button_level5");
    buttonLevel5->setTouchEnabled(true);
    buttonLevel5->addClickEventListener([=](Ref*)
        {
            gotoPlayLayer(this, 5);
        });

    auto buttonLevel6 = utils::findChild<ui::Button*>(this, "Button_level6");
    buttonLevel6->setTouchEnabled(true);
    buttonLevel6->addClickEventListener([=](Ref*)
        {
            gotoPlayLayer(this, 6);
        });

    auto buttonLevel7 = utils::findChild<ui::Button*>(this, "Button_level7");
    buttonLevel7->setTouchEnabled(true);
    buttonLevel7->addClickEventListener([=](Ref*)
        {
            gotoPlayLayer(this, 7);
        });

    auto buttonLevel8 = utils::findChild<ui::Button*>(this, "Button_level8");
    buttonLevel8->setTouchEnabled(true);
    buttonLevel8->addClickEventListener([=](Ref*)
        {
            gotoPlayLayer(this, 8);
        });

}

void InterfaceGame::gotoPlayLayer(cocos2d::Ref* sender , int _level)
{
    // init level1;
    auto playLayer = PlayLayer::createScene(_level);
 
    Director::getInstance()->replaceScene(TransitionFade::create(0.2, playLayer));
}

void InterfaceGame::menuCloseCallback(Ref* pSender)
{
    Director::getInstance()->end();
}
