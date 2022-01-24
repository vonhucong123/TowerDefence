#include "startGame.h"
#include "SimpleAudioEngine.h"
#include "Data.h"
#include "InterFaceGame.h"

#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
#include <iostream>

USING_NS_CC;

Scene* startGame::createScene()
{
    auto scene = Scene::create();
    auto layer = startGame::create();
    scene->addChild(layer);
    return scene;
}

static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

bool startGame::init()
{
    if (!Layer::init())
    {
        return false;
    }

    auto visibleSize = Director::getInstance()->getVisibleSize();

    Vec2 origin = Director::getInstance()->getVisibleOrigin();


    auto mainMenu = CSLoader::getInstance()->createNode("csb/startGame.csb");
    this->addChild(mainMenu);
    
    initSetting();

    initRegistration();

    initLogin();

    m_userData.loadFileJson("userData.json");

  
    return true;
}

void startGame::menuCloseCallback(Ref* pSender)
{
    Director::getInstance()->end();
}

void startGame::initSetting()
{
    // open Setting
    auto buttonSetting = utils::findChild<ui::Button*>(this, "ButtonSetting");
    buttonSetting->setTouchEnabled(true);
    buttonSetting->addClickEventListener([=](Ref*)
        {
            utils::findChild<ui::ImageView*>(this, "SettingTable")->setVisible(true);
        });

    // close Setting
    auto closeSetting = utils::findChild<ui::Button*>(this, "ButtonCloseSetting");
    closeSetting->setTouchEnabled(true);
    closeSetting->addClickEventListener([=](Ref*)
        {
            utils::findChild<ui::ImageView*>(this, "SettingTable")->setVisible(false);
        });

    // set sound on (off->on)
    auto soundOn = utils::findChild<ui::Button*>(this, "Button_SoundOn");
    soundOn->setTouchEnabled(true);
    soundOn->addClickEventListener([=](Ref*)
        {
            utils::findChild<ui::Button*>(this, "Button_SoundOff")->setVisible(true);
            utils::findChild<ui::Button*>(this, "Button_SoundOn")->setVisible(false);
        });

    // set sound off (on->off)
    auto soundOff = utils::findChild<ui::Button*>(this, "Button_SoundOff");
    soundOff->setTouchEnabled(true);
    soundOff->addClickEventListener([=](Ref*)
        {
            utils::findChild<ui::Button*>(this, "Button_SoundOn")->setVisible(true);
            utils::findChild<ui::Button*>(this, "Button_SoundOff")->setVisible(false);
        });

    // set music on (off->on)
    auto musicOn = utils::findChild<ui::Button*>(this, "Button_MusicOn");
    musicOn->setTouchEnabled(true);
    musicOn->addClickEventListener([=](Ref*)
        {
            utils::findChild<ui::Button*>(this, "Button_MusicOff")->setVisible(true);
            utils::findChild<ui::Button*>(this, "Button_MusicOn")->setVisible(false);
        });

    // set music off (on->off)
    auto musicOff = utils::findChild<ui::Button*>(this, "Button_MusicOff");
    musicOff->setTouchEnabled(true);
    musicOff->addClickEventListener([=](Ref*)
        {
            utils::findChild<ui::Button*>(this, "Button_MusicOn")->setVisible(true);
            utils::findChild<ui::Button*>(this, "Button_MusicOff")->setVisible(false);
        });

    // set vibration on (off->on)
    auto vibrationOn = utils::findChild<ui::Button*>(this, "Button_VibrationOn");
    vibrationOn->setTouchEnabled(true);
    vibrationOn->addClickEventListener([=](Ref*)
        {
            utils::findChild<ui::Button*>(this, "Button_VibrationOff")->setVisible(true);
            utils::findChild<ui::Button*>(this, "Button_VibrationOn")->setVisible(false);
        });

    // set vibration off (on->off)
    auto vibrationOff = utils::findChild<ui::Button*>(this, "Button_VibrationOff");
    vibrationOff->setTouchEnabled(true);
    vibrationOff->addClickEventListener([=](Ref*)
        {
            utils::findChild<ui::Button*>(this, "Button_VibrationOn")->setVisible(true);
            utils::findChild<ui::Button*>(this, "Button_VibrationOff")->setVisible(false);
        });
}

void startGame::initRegistration()
{
    // open reg
    auto regTable = utils::findChild<ui::Button*>(this, "Button_Reg");
    regTable->setTouchEnabled(true);
    regTable->addClickEventListener([=](Ref*)
        {
            utils::findChild<ui::ImageView*>(this, "RegTable")->setVisible(true);
        });

    // close reg
    auto closeRegTable = utils::findChild<ui::Button*>(this, "Button_closeReg");
    closeRegTable->setTouchEnabled(true);
    closeRegTable->addClickEventListener([=](Ref*)
        {
            utils::findChild<ui::ImageView*>(this, "RegTable")->setVisible(false);
        });

    // create accout
    auto createAccout = utils::findChild<ui::Button*>(this, "Button_Create");
    createAccout->setTouchEnabled(true);
    createAccout->addClickEventListener([=](Ref*)
        {
            auto inputAccout = utils::findChild<ui::TextField*>(this, "inputAcount");
            auto inputPass = utils::findChild<ui::TextField*>(this, "inputPass");
            std::string _name = inputAccout->getString();
            std::string _pass = inputPass->getString();
            // save accout
            //m_userData.loadFileJson();
            //m_userData.saveAccout();
            
            utils::findChild<ui::ImageView*>(this, "RegTable")->setVisible(false);
        });
}

void startGame::initLogin()
{
    // hiển thị bảng đăng nhập
    auto loginTable = utils::findChild<ui::Button*>(this, "ButtonPlay");
    loginTable->setTouchEnabled(true);
    loginTable->addClickEventListener([=](Ref*)
        {
            utils::findChild<ui::ImageView*>(this, "LoginTable")->setVisible(true);
        });
    
    // tắt màn đăng nhập
    auto closeLoginTable = utils::findChild<ui::Button*>(this, "Button_closeLogin");
    closeLoginTable->setTouchEnabled(true);
    closeLoginTable->addClickEventListener([=](Ref*)
        {
            utils::findChild<ui::ImageView*>(this, "LoginTable")->setVisible(false);
        });

    // cài đặt nút ấn mũi tên
    auto buttonPlay = utils::findChild<ui::Button*>(this, "Button_Play");
    buttonPlay->setTouchEnabled(true);
    buttonPlay->addClickEventListener([=](Ref*)
        {
            // check accout
            auto inputAccout = utils::findChild<ui::TextField*>(this, "inputNameLogin");
            auto inputPass = utils::findChild<ui::TextField*>(this, "inputPassLogin");
            std::string _name = inputAccout->getString();
            std::string _pass = inputPass->getString();
            m_userData.setPassWord(_pass);
            m_userData.setUserName(_name);
            CCLOG(_name.c_str());
            CCLOG(_pass.c_str());
            if (m_userData.isAccoutAvariable())
            {
                CCLOG("pass login");
                this->goToInterfaceGame();
            }
            else
            {
                inputAccout->setString("");
                inputPass->setString("");
            }

        });
}

void startGame::soundSetting()
{

}

void startGame::musicSetting()
{
}

void startGame::goToInterfaceGame()
{
    auto playLayer = InterfaceGame::createScene();
    Director::getInstance()->replaceScene(TransitionFade::create(0.2, playLayer));
}
