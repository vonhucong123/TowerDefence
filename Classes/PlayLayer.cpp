#include "InterFaceGame.h"
#include "SimpleAudioEngine.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
#include "Army.h"
#include "Enemy.h"
#include "PlayLayer.h"
#include "SupportTower.h"
#include "ArcherTower.h"
#include "StoneTower.h"
#include "MagicTower.h"
#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;
USING_NS_CC;

Scene* PlayLayer::createScene(int _level)
{
    auto scene = Scene::createWithPhysics();
    scene->getPhysicsWorld()->setDebugDrawMask(cocos2d::PhysicsWorld::DEBUGDRAW_ALL);
    
    // cài đặt không trọng lực
    scene->getPhysicsWorld()->setGravity(Vec2(0, 0));

    auto layer = PlayLayer::create();
    layer->setPhysicsWorld(scene->getPhysicsWorld());
    layer->m_numOfLevel = _level;
    layer->initScene();
    scene->addChild(layer);

    return scene;
}

static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

bool PlayLayer::init()
{
    if (!Layer::init())
    {
        return false;
    }
    return true;
}
void PlayLayer::initScene() 
{
    auto visibleSize = Director::getInstance()->getVisibleSize();

    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    initLevel();

    initButton();

    createGoldAndHeartDisplay();

    initTimerCreateEnemyWare();

    // sau một giây kiểm tra va chạm
    this->schedule(schedule_selector(PlayLayer::initScheduleCheckWar, ), 1.5);
    this->schedule(schedule_selector(PlayLayer::checkDistanceArcherTower, ), 1);
    this->schedule(schedule_selector(PlayLayer::updateObjectHealth, ), 0.01);
    this->schedule(schedule_selector(PlayLayer::checkEnemyAndArmy, ), 0.5);
    this->schedule(schedule_selector(PlayLayer::checkFinishLevel, ), 0.5);

    // cài đặt sự kiện chạm tay vào màn hình
    auto touchListener = EventListenerTouchOneByOne::create();
    touchListener->onTouchBegan = CC_CALLBACK_2(PlayLayer::onTouchBegan, this);
    touchListener->onTouchEnded = CC_CALLBACK_2(PlayLayer::onTouchEnded, this);
    touchListener->onTouchMoved = CC_CALLBACK_2(PlayLayer::onTouchMove, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, this);

}
void PlayLayer::initLevel()
{
    auto visibleSize = Director::getInstance()->getVisibleSize();

    string _level = "Level" + to_string(m_numOfLevel);
    
    m_Level->loadFileJson("Level.json");
    string csbFileName = m_Level->getStringOfMember(_level, "MapLevel");

    auto mainMenu = CSLoader::getInstance()->createNode("csb/" + csbFileName);
    this->addChild(mainMenu);

    // load ware
    m_numEnemy.push_back(m_Level->getIntOfMember(_level, "Ware1"));
    m_numEnemy.push_back(m_Level->getIntOfMember(_level, "Ware2"));
    m_numEnemy.push_back(m_Level->getIntOfMember(_level, "Ware3"));
    m_numEnemy.push_back(m_Level->getIntOfMember(_level, "Ware4"));
    m_numEnemy.push_back(m_Level->getIntOfMember(_level, "Ware5"));

    // load line
    setLineForEmemy();

    // init node 
    auto pointNode = Node::create();
    auto pointBody = PhysicsBody::createCircle(30); 
    pointBody->setCollisionBitmask(1);  
    pointBody->setContactTestBitmask(true);
    pointBody->setDynamic(false);
    pointNode->setPhysicsBody(pointBody);
    pointNode->setPosition(m_Level->getIntOfMember(_level, "Point21x"), m_Level->getIntOfMember(_level, "Point21y"));
    this->addChild(pointNode);

    // setup physic contact
    auto contactListener = EventListenerPhysicsContact::create();
    contactListener->onContactBegin = CC_CALLBACK_1(PlayLayer::onContactBegin, this);
    this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(contactListener, this);

}

void PlayLayer::initButton()
{
    auto Button_undo = utils::findChild<ui::Button*>(this, "Button_Return");
    Button_undo->addClickEventListener([=](Ref*)
        {
            gotoInterFaceGame(this);
        });
    string _level = "Level" + to_string(m_numOfLevel);
    int _numDot = m_Level->getIntOfMember(_level, "numDot") + 1;
    for (int i = 1; i < _numDot; i++)
    {
        string _nameButton = "Button_Dot_" + to_string(i);
        auto Button_Dot = utils::findChild<ui::Button*>(this, _nameButton);
        Button_Dot->setTouchEnabled(true);
        Button_Dot->addClickEventListener([=](Ref*)
            {
                for (int j = 1; j < _numDot; j++)
                {
                    // hide all TableTower
                    string _nameTableTower = "Table_Tower" + to_string(j);
                    auto Table_Tower = utils::findChild<ui::ImageView*>(this, _nameTableTower);
                    Table_Tower->setVisible(false);
                    Table_Tower->setTouchEnabled(false);                                     
                }

                // show current Table Tower
                string _nameTableTower = "Table_Tower" + to_string(i);
                auto Table_Tower = utils::findChild<ui::ImageView*>(this, _nameTableTower);
                Table_Tower->setVisible(true);
                Table_Tower->setTouchEnabled(true);

                // build tower in cur position
                {
                    string _towerName1 = "Button_SupportTower" + to_string(i);
                    string _towerName2 = "Button_ArcherTower" + to_string(i);
                    string _towerName3 = "Button_MagicTower" + to_string(i);
                    string _towerName4 = "Button_StoneTower" + to_string(i);
                    auto Button_Tower1 = utils::findChild<ui::Button*>(this, _towerName1);
                    Button_Tower1->addClickEventListener([=](Ref*)
                        {
                            // if enough gold
                            if (buildSupportTower(Button_Dot->getPosition()))
                            {
                                CCLOG("Button_SupportTower");
                                Button_Dot->setVisible(false);
                                Table_Tower->setVisible(false);
                            }                           
                        });
                    auto Button_Tower2 = utils::findChild<ui::Button*>(this, _towerName2);
                    Button_Tower2->addClickEventListener([=](Ref*)
                        {
                            if (buildArcherTower(Button_Dot->getPosition()))
                            {
                                Button_Dot->setVisible(false);
                                Table_Tower->setVisible(false);
                                CCLOG("Button_ArcherTower");
                            }                           
                        });
                    auto Button_Tower3 = utils::findChild<ui::Button*>(this, _towerName3);
                    Button_Tower3->addClickEventListener([=](Ref*)
                        {
                            if (buildMagicTower(Button_Dot->getPosition()))
                            {
                                Button_Dot->setVisible(false);
                                Table_Tower->setVisible(false);
                                CCLOG("Button_MagicTower");
                            }                            
                        });
                    auto Button_Tower4 = utils::findChild<ui::Button*>(this, _towerName4);
                    Button_Tower4->addClickEventListener([=](Ref*)
                        {
                            if (buildStoneTower(Button_Dot->getPosition()))
                            {
                                Button_Dot->setVisible(false);
                                Table_Tower->setVisible(false);
                                CCLOG("Button_StoneTower");
                            }                          
                        });
                }             
            }
        );
    }
}

void PlayLayer::initEnemy(float dt)
{
    if(m_ware != -1)
    {
        int _lastEnemyArraySize = m_EnemyArray.size();
        for (int i = 0; i < m_numEnemy[m_ware]; i++)
        {
            Enemy* enemy = new Enemy();

            Sprite* character = enemy->getEnemyCharacter();
            auto enemyBody = PhysicsBody::createEdgeBox((character->getContentSize()) / 2);
            enemyBody->setPositionOffset(Vec2(-15, -10));
            enemyBody->setCollisionBitmask(2);
            enemyBody->setContactTestBitmask(true);
            enemyBody->setDynamic(false);
            character->setPhysicsBody(enemyBody);
            this->addChild(character);
            this->addChild(enemy->getHealthBar());
            m_EnemyArray.push_back(enemy);
        }
        m_ware++;        

        // set sequence action 
        for (int i = _lastEnemyArraySize; i < m_EnemyArray.size(); i++)
        {
            vector<MoveTo*> movetoList;
            // time random 0.8 - 1
            float random = ((float)rand()) / (float)RAND_MAX * 1.0;
            float _time = 0.8 + (random * (1 - 0.8));
            for (int j = 0; j < m_LineForEnemy.size(); j++)
            {
                int _rad = rand() % (50 - 1 + 1) + 1;
                MoveTo* _moveto = MoveTo::create(_time, Point(m_LineForEnemy[j].x + _rad, m_LineForEnemy[j].y + _rad));
                movetoList.push_back(_moveto);
            }

            m_movetoList.push_back(movetoList);

            // set first position for Enemy
            m_EnemyArray[i]->getEnemyCharacter()->setPosition(m_LineForEnemy[0]);
        }

        for (int i = _lastEnemyArraySize; i < m_EnemyArray.size(); i++)
        {
            auto seq = Sequence::create(
                m_movetoList[i][0],
                m_movetoList[i][1],
                m_movetoList[i][2],
                m_movetoList[i][3],
                m_movetoList[i][4],
                m_movetoList[i][5],
                m_movetoList[i][6],
                m_movetoList[i][7],
                m_movetoList[i][8],
                m_movetoList[i][9],
                m_movetoList[i][10],
                m_movetoList[i][11],
                m_movetoList[i][12],
                m_movetoList[i][13],
                m_movetoList[i][14],
                m_movetoList[i][15],
                m_movetoList[i][16],
                m_movetoList[i][17],
                m_movetoList[i][18],
                m_movetoList[i][19],
                nullptr);
            m_EnemyArray[i]->getEnemyCharacter()->runAction(seq);

        }
    }
    CCLOG("Ware: %d", m_ware);
    if (m_numEnemy[m_ware] == m_numEnemy[m_numEnemy.size() - 1])
    {
        CCLOG("finished");
        m_ware = -1;
    }
}

void PlayLayer::initTimerCreateEnemyWare()
{

    auto nextWare = utils::findChild<ui::Button*>(this, "Button_skull");
    nextWare->addClickEventListener([=](Ref*)
        {
            if (m_ware != -1)
            {
                initEnemy(1);
                m_timerWare->setPercentage(100);
                m_timerWare->runAction(ProgressFromTo::create(20, 100, 0));
            }
        });
    m_timerWare = ProgressTimer::create(Sprite::create("td-gui/interface_game/skull_bg.png"));
    m_timerWare->setType(ProgressTimer::Type::RADIAL);
    m_timerWare->setMidpoint(Vec2(0.5f, 0.5f));
    m_timerWare->setReverseDirection(true);
    m_timerWare->setPercentage(100);
    m_timerWare->setScale(0.30);
    m_timerWare->setPosition(nextWare->getPosition());
    this->addChild(m_timerWare);
    m_timerWare->runAction(ProgressFromTo::create(20, 100, 0));
}

void PlayLayer::createGoldAndHeartDisplay()
{
    // load data in json
    auto text_gold = utils::findChild<ui::Text*>(this, "Text_Gold");
    text_gold->setString(to_string(m_gold));

    auto text_heart = utils::findChild<ui::Text*>(this, "Text_Heart");
    text_heart->setString(to_string(m_Heart));
}

void PlayLayer::initScheduleCheckWar(float dt)
{
    checkTimerForWare();
    checkDistanceMagicTower();
    checkDistanceToneTower();
}

bool PlayLayer::buildSupportTower(cocos2d::Point _point)
{
    if (m_gold >= 150)
    {
        SupportTower* _supportTower = new SupportTower(Point(_point.x, _point.y + 30));

        m_SupportTowerList.push_back(_supportTower);
        this->addChild(_supportTower->getSupportTowerSprite());
        for (int i = 0; i < _supportTower->getArmyList().size(); i++)
        {
            // create physicbox
            Sprite* character = _supportTower->getArmyList()[i]->getArmyCharacter();
            auto armyBody = PhysicsBody::createEdgeBox((character->getContentSize()) / 2);
            armyBody->setPositionOffset(Vec2(-15, -10));
            armyBody->setCollisionBitmask(3);
            armyBody->setContactTestBitmask(true);
            armyBody->setDynamic(false);
            // apply to character
            character->setPhysicsBody(armyBody);
            this->addChild(_supportTower->getArmyList()[i]->getArmyCharacter());
        }

        // minus gold from gold of player;
        this->updateGold("minus150");

        return true;
    }
    else
    {
        return false;
    }
}

void PlayLayer::setFlagForSupportTower(cocos2d::Point _point)
{
    auto _flag = Sprite::create("support_tower/18.png");
    _flag->setPosition(_point);
    _flag->setScale(0.5);
    this->addChild(_flag);
    m_flagOfSupportTowerList.push_back(_flag);
}

void PlayLayer::delFlagForSupportTower(int idx)
{
    // del idx element
    m_flagOfSupportTowerList.erase(m_flagOfSupportTowerList.begin() + idx);
}

bool PlayLayer::buildArcherTower(cocos2d::Point _point)
{
    if (m_gold >= 100)
    {
        ArcherTower* _archerTower = new ArcherTower(Point(_point.x, _point.y + 30));
        vector<Army*> _archerArmyList = _archerTower->getArcherArmyVector();
        m_ArcherTowerList.push_back(_archerTower);

        for (int i = 0; i < _archerArmyList.size(); i++)
        {
            auto armycharacter = _archerArmyList[i]->getArmyCharacter();
            this->addChild(armycharacter);
            armycharacter->setScale(0.6);
        }
        this->addChild(_archerTower->getArcherTowerSprite());

        // minus gold from gold of player;
        this->updateGold("minus100");

        return true;
    }
    else
    {
        return false;
    }
}

bool PlayLayer::buildMagicTower(cocos2d::Point _point)
{
    if (m_gold >= 100)
    {
        MagicTower* _magicTower = new MagicTower(Point(_point.x, _point.y + 30));
        auto _magicBox = PhysicsBody::createCircle(200);
        _magicBox->setDynamic(false);
        _magicBox->setContactTestBitmask(true);
        _magicTower->getMagicTowerSprite()->setPhysicsBody(_magicBox);
        m_MagicTowerList.push_back(_magicTower);
        this->addChild(_magicTower->getMagicTowerSprite());
        this->addChild(_magicTower->getHeadMagicTowerSprite());

        // minus gold from gold of player;
        this->updateGold("minus100");

        return true;
    }
    else
    {
        return false;
    }
}

bool PlayLayer::buildStoneTower(cocos2d::Point _point)
{
    if (m_gold >= 120)
    {
        StoneTower* _stoneTower = new StoneTower(Point(_point.x, _point.y + 10));

        this->addChild(_stoneTower->getHeadStoneTowerLeftSprite(), 100);
        this->addChild(_stoneTower->getHeadStoneTowerRightSprite(), 100);
        this->addChild(_stoneTower->getStoneTowerSprite(), 100);
        this->addChild(_stoneTower->getStoneSprite(), 100);
        this->addChild(_stoneTower->getStoneBreakSprite(), 100);

        // test action 
        _stoneTower->getHeadStoneTowerLeftSprite()->runAction(RepeatForever::create(_stoneTower->getHeadStoneTowerLeftSequence()));
        _stoneTower->getHeadStoneTowerLeftSprite()->pauseSchedulerAndActions();

        _stoneTower->getHeadStoneTowerRightSprite()->runAction(RepeatForever::create(_stoneTower->getHeadStoneTowerRightSequence()));
        _stoneTower->getHeadStoneTowerRightSprite()->pauseSchedulerAndActions();

        _stoneTower->getStoneSprite()->runAction(RepeatForever::create(_stoneTower->getStoneFlyUpSequence()));
        _stoneTower->getStoneSprite()->pauseSchedulerAndActions();

        //_stoneTower->getStoneSprite()->runAction(_stoneTower->getStoneFlyDownSequence(Point(500, 500)));
        m_StoneTowerList.push_back(_stoneTower);

        // minus gold from gold of player;
        this->updateGold("minus120");

        return true;
    }
    else return false;
}

void PlayLayer::setLineForEmemy()
{
    string _level = "Level" + to_string(m_numOfLevel);
    int _numPoint = m_Level->getIntOfMember(_level, "numPoint");
    for (int i = 1; i < _numPoint; i++)
    {
        string _x, _y;
        _x = "Point" + to_string(i) + "x";
        _y = "Point" + to_string(i) + "y";
        string _level = "Level" + to_string(m_numOfLevel);
        int x = m_Level->getIntOfMember(_level, _x);
        int y = m_Level->getIntOfMember(_level, _y);
        m_LineForEnemy.push_back(Point(x, y));
    }
}

bool PlayLayer::onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event)
{
    // hide 4 option
    string _level = "Level" + to_string(m_numOfLevel);
    int _numTableTower = m_Level->getIntOfMember(_level, "numDot");
    for (int i = 1; i < _numTableTower; i++)
    {
        string _table_name = "Table_Tower" + to_string(i);
        auto Table_Tower = utils::findChild<ui::ImageView*>(this, _table_name);
        Table_Tower->setVisible(false);
    }

    // set sprite touch for support
    cocos2d::Vec2 p = touch->getLocation();
    if (m_SupportTowerList.size() != 0)
    {
        for (int i = 0; i < m_SupportTowerList.size(); i++)
        {
            cocos2d::Rect rect = m_SupportTowerList[i]->getSupportTowerSprite()->getBoundingBox();
            if (rect.containsPoint(p))
            {
                CCLOG("clicked Support");
                if (m_SupportTowerList[i]->getIdxFlag() == -1)
                {
                    m_SupportTowerList[i]->setIndexFlag(i);
                    setFlagForSupportTower(p);
                }                             
            }

        }
    }

    // set sprite archer touch event
    if (m_ArcherTowerList.size() != 0)
    {
        for (int i = 0; i < m_ArcherTowerList.size(); i++)
        {
            cocos2d::Rect rect = m_ArcherTowerList[i]->getArcherTowerSprite()->getBoundingBox();
            if (rect.containsPoint(p))
            {
                // so you touched the Sprite, do something about it
                CCLOG("clicked Archer");
                //upgradeTower(ARCHER_TOWER);
            }
        }
    }

    // set sprite stone touch event
    if (m_StoneTowerList.size() != 0)
    {
        for (int i = 0; i < m_StoneTowerList.size(); i++)
        {
            cocos2d::Rect rect = m_StoneTowerList[i]->getStoneTowerSprite()->getBoundingBox();
            if (rect.containsPoint(p))
            {
                // so you touched the Sprite, do something about it
                CCLOG("clicked Stone");
                //upgradeTower(STONE_TOWER);
            }
        }
    }

    // set sprite Magic touch event
    if (m_MagicTowerList.size() != 0)
    {
        for (int i = 0; i < m_MagicTowerList.size(); i++)
        {
            cocos2d::Rect rect = m_MagicTowerList[i]->getMagicTowerSprite()->getBoundingBox();
            if (rect.containsPoint(p))
            {
                // so you touched the Sprite, do something about it
                CCLOG("clicked Magic");
                //upgradeTower(MAGIC_TOWER);
            }
        }
    }

    return true;
}

void PlayLayer::onTouchMove(cocos2d::Touch* touch, cocos2d::Event* event)
{
    cocos2d::Vec2 p = touch->getLocation();

    for (int i = 0; i < m_SupportTowerList.size(); i++)
    {
        if (m_SupportTowerList[i]->getIdxFlag() != -1)
        {
            cocos2d::Rect rect = m_flagOfSupportTowerList[i]->getBoundingBox();
            if (rect.containsPoint(p))
            {
                if (p.getDistance(m_SupportTowerList[i]->getSupportTowerSprite()->getPosition()) < 200)
                {
                    m_flagOfSupportTowerList[i]->setPosition(p);
                }
            }
        }                
    }
}

void PlayLayer::onTouchEnded(cocos2d::Touch* touch, cocos2d::Event* event)
{
    cocos2d::Vec2 p = touch->getLocation();

    for (int i = 0; i < m_SupportTowerList.size(); i++)
    {
        cocos2d::Rect rect = m_flagOfSupportTowerList[i]->getBoundingBox();
        if (rect.containsPoint(p))
        {
            for (int j = 0; j < m_SupportTowerList[i]->getArmyList().size(); j++)
            {
                if ((m_SupportTowerList[i]->getIdxFlag()) != -1)
                {
                    auto _moveto = MoveTo::create(2, p);
                    m_SupportTowerList[i]->getArmyList()[j]->getArmyCharacter()->runAction(_moveto);
                    m_SupportTowerList[i]->getArmyList()[j]->characterAnimation(10);

                }
            }
        }
            
    }
}


void PlayLayer::menuCloseCallback(Ref* pSender)
{
    Director::getInstance()->end();
}

void PlayLayer::setPhysicsWorld(cocos2d::PhysicsWorld* _world)
{
    world = _world;
}

void PlayLayer::gotoInterFaceGame(cocos2d::Ref* sender)
{
    auto interfacegame = InterfaceGame::createScene();
    Director::getInstance()->replaceScene(TransitionFade::create(0.2, interfacegame));
}

void PlayLayer::upgradeTower(int _type)
{
    if (_type == SUPPORT_TOWER)
    {
        
    }
    if (_type == ARCHER_TOWER)
    {

    }
    if (_type == STONE_TOWER)
    {

    }
    if (_type == MAGIC_TOWER)
    {

    }
}

void PlayLayer::updateObjectHealth (float dt)
{
    for (int i = 0; i < m_EnemyArray.size(); i++)
    {   
        if (m_EnemyArray[i]->getHealthBar()->getPercentage() > 0)
        {
            if (auto character = m_EnemyArray[i]->getEnemyCharacter())
            {
                m_EnemyArray[i]->getHealthBar()->setPosition(
                    m_EnemyArray[i]->getEnemyCharacter()->getPosition().x,
                    m_EnemyArray[i]->getEnemyCharacter()->getPosition().y + m_EnemyArray[i]->getEnemyCharacter()->getContentSize().height / 9);
                m_EnemyArray[i]->setHealthBar(m_EnemyArray[i]->getHealth());
            }           
        }
        else
        {
            if (auto enemy = m_EnemyArray[i]->getEnemyCharacter())
            {
                // remove enemy from vector
                enemy->removeFromParent();               
                m_EnemyArray.erase(m_EnemyArray.begin() + i);
                m_movetoList.erase(m_movetoList.begin() + i);    
                // plus gold for player
                this->updateGold("plus20");
                
            }
        }
                      
    }
}

void PlayLayer::checkDistanceArcherTower(float dt)
{
    for (int i = 0; i < m_ArcherTowerList.size(); i++)
    {
        auto _sourcePos = m_ArcherTowerList[i]->getArcherTowerSprite()->getPosition();
        int _bestEnemy = 100;
        int _idxEnemy = 0;
        bool _hasEnemyInDistance = false;
        for (int j = 0; j < m_EnemyArray.size(); j++)
        {
            auto _enemy = m_EnemyArray[j];
            if (_enemy)
            {
                if (_sourcePos.distance(m_EnemyArray[j]->getEnemyCharacter()->getPosition()) < 200)
                {
                    _hasEnemyInDistance = true;
                    if (_bestEnemy >= m_EnemyArray[j]->getHealth())
                    {
                        _bestEnemy = m_EnemyArray[j]->getHealth();
                        _idxEnemy = i;
                    }
                    
                    // check for run action archer army
                    auto archerArmyList = m_ArcherTowerList[i]->getArcherArmyVector();
                    for (int k = 0; k < archerArmyList.size(); k++)
                    {
                        auto animate = m_ArcherTowerList[i]->getArcherArmyAnimate();
                        if (archerArmyList[k]->getArmyCharacter()->getNumberOfRunningActions() == 0)
                        {
                            archerArmyList[k]->getArmyCharacter()->runAction(animate);
                        }                      
                    }
                }
            }          
        } 

        // stop run action archer army
        if (_hasEnemyInDistance == false)
        {
            auto archerArmyList = m_ArcherTowerList[i]->getArcherArmyVector();
            for (int k = 0; k < archerArmyList.size(); k++)
            {       
                // if running
                if (archerArmyList[k]->getArmyCharacter()->getNumberOfRunningActions() != 0)
                {
                    archerArmyList[k]->getArmyCharacter()->stopAllActions();
                }              
            }
        }

        if ((_idxEnemy < m_EnemyArray.size())&& (_sourcePos.distance(m_EnemyArray[_idxEnemy]->getEnemyCharacter()->getPosition()) < 200))
        {
            m_EnemyArray[_idxEnemy]->setHealth(m_EnemyArray[_idxEnemy]->getHealth() - 30); 

            this->addChild(m_ArcherTowerList[i]->getArrowOfArcherTowerSprite());

        }
        else
        {
            for (int j = 0; j < m_EnemyArray.size(); j++)
            {
                auto _enemy = m_EnemyArray[j];
                if (_enemy)
                {
                    if (_sourcePos.distance(m_EnemyArray[j]->getEnemyCharacter()->getPosition()) < 200)
                    {
                        m_EnemyArray[j]->setHealth(m_EnemyArray[j]->getHealth() - 30);

                        this->addChild(m_ArcherTowerList[i]->getArrowOfArcherTowerSprite());
                        break;
                    }
                }
            }
        }                
    }  
}

void PlayLayer::checkDistanceMagicTower()
{
    for (int i = 0; i < m_MagicTowerList.size(); i++)
    {
        auto _sourcePos = m_MagicTowerList[i]->getMagicTowerSprite()->getPosition();

        for (int j = 0; j < m_EnemyArray.size(); j++)
        {
            if (m_EnemyArray[j]->getEnemyCharacter() != NULL)
            {
                if (_sourcePos.distance(m_EnemyArray[j]->getEnemyCharacter()->getPosition()) < 200)
                {
                    CCLOG("MagicTower Ban");
                }
            }
        }
    }
}

void PlayLayer::checkDistanceToneTower()
{
    for (int i = 0; i < m_StoneTowerList.size(); i++)
    {
        auto _sourcePos = m_StoneTowerList[i]->getStoneTowerSprite()->getPosition();
        for (int j = 0; j < m_EnemyArray.size(); j++)
        {
            if (m_EnemyArray[j]->getEnemyCharacter() != NULL)
            {
                if (_sourcePos.distance(m_EnemyArray[j]->getEnemyCharacter()->getPosition()) < 200)
                {
                    CCLOG("Stone Tower ban");
                    m_StoneTowerList[i]->getStoneSprite()->setVisible(true);
                    m_StoneTowerList[i]->getHeadStoneTowerLeftSprite()->resumeSchedulerAndActions();
                    m_StoneTowerList[i]->getHeadStoneTowerRightSprite()->resumeSchedulerAndActions();
                    m_StoneTowerList[i]->getStoneSprite()->resumeSchedulerAndActions();

                    auto stoneBreak = m_StoneTowerList[i]->getStoneFlyDownSequence(m_EnemyArray[j]->getEnemyCharacter()->getPosition());
                    m_StoneTowerList[i]->getStoneBreakSprite()->runAction(stoneBreak);
                    m_StoneTowerList[i]->getStoneBreakSprite()->setVisible(true);

                    m_EnemyArray[j]->setHealth(m_EnemyArray[j]->getHealth() - 40);
                    break;
                }
                else
                {
                    m_StoneTowerList[i]->getHeadStoneTowerLeftSprite()->pauseSchedulerAndActions();
                    m_StoneTowerList[i]->getHeadStoneTowerRightSprite()->pauseSchedulerAndActions();
                    m_StoneTowerList[i]->getStoneSprite()->pauseSchedulerAndActions();
                    m_StoneTowerList[i]->getStoneSprite()->setVisible(false);
                }
            }
        }
        if (m_EnemyArray.size() == 0)
        {
            m_StoneTowerList[i]->getHeadStoneTowerLeftSprite()->pauseSchedulerAndActions();
            m_StoneTowerList[i]->getHeadStoneTowerRightSprite()->pauseSchedulerAndActions();
            m_StoneTowerList[i]->getStoneSprite()->pauseSchedulerAndActions();
            m_StoneTowerList[i]->getStoneSprite()->setVisible(false);
        }
    }
}

void PlayLayer::checkEnemyAndArmy(float dt)
{
    for (int i = 0; i < m_EnemyArray.size(); i++)
    {
        auto _sourcePos = m_EnemyArray[i]->getEnemyCharacter()->getPosition();
        for (int j = 0; j < m_SupportTowerList.size(); j++)
        {
            for (int k = 0; k < m_SupportTowerList[j]->getArmyList().size(); k++)
            {
                auto pos = m_SupportTowerList[j]->getArmyList()[k]->getArmyCharacter()->getPosition();
                if (_sourcePos.distance(pos) < 100)
                {
                    
                    //MoveTo::create(1, pos);
                  
                }
                else
                {
                    //m_EnemyArray[i]->getEnemyCharacter()->resumeSchedulerAndActions();
                }
            }
        }
        
    }
}

void PlayLayer::checkTimerForWare()
{
    if (m_ware != -1)
    {
        if (m_timerWare!= NULL)
        {
            if (m_timerWare->getPercentage() <= 0)
            {
                m_timerWare->setPercentage(100);
                m_timerWare->runAction(ProgressFromTo::create(20, 100, 0));
                initEnemy(1);
            }
        }
    }
}

void PlayLayer::checkFinishLevel(float dt)
{
    //check fail
    if (m_Heart == 0)
    {
        this->removeAllChildren();
        string _level = "Level" + to_string(m_numOfLevel);
        string csbFileName = m_Level->getStringOfMember(_level, "MapLevel");
        auto mainMenu = CSLoader::getInstance()->createNode("csb/" + csbFileName);
        this->addChild(mainMenu);

        m_SupportTowerList.clear();
        m_EnemyArray.clear();
        m_ArcherTowerList.clear();
        m_StoneTowerList.clear();
        m_MagicTowerList.clear();
        m_timerWare = NULL;

        CCLOG("sdjdjd");
        auto failed = utils::findChild<ui::ImageView*>(this, "Level_fail");
        failed->setVisible(true);
        failed->setZOrder(1000);

        auto Button_back = utils::findChild<ui::Button*>(this, "Button_back");
        Button_back->addClickEventListener([=](Ref*)
            {
                gotoInterFaceGame(this);
            });

        auto Button_restart = utils::findChild<ui::Button*>(this, "Button_restart");
        Button_restart->addClickEventListener([=](Ref*)
            {
                auto playLayer = PlayLayer::createScene(m_numOfLevel);

                Director::getInstance()->replaceScene(TransitionFade::create(0.2, playLayer));
            });
    }

    // check win
    if ((m_ware == -1) && m_EnemyArray.size() == 0)
    {
        this->removeAllChildren();

        string _level = "Level" + to_string(m_numOfLevel);
        string csbFileName = m_Level->getStringOfMember(_level, "MapLevel");

        auto mainMenu = CSLoader::getInstance()->createNode("csb/" + csbFileName);
        this->addChild(mainMenu);

        m_SupportTowerList.clear();
        m_EnemyArray.clear();
        m_ArcherTowerList.clear();
        m_StoneTowerList.clear();
        m_MagicTowerList.clear();
        m_timerWare = NULL;

        auto Level_Win = utils::findChild<ui::ImageView*>(this, "Level_Win");
        Level_Win->setVisible(true);
        Level_Win->setZOrder(90000);
        Level_Win->setLocalZOrder(9999999);

        auto Button_WinMenu = utils::findChild<ui::Button*>(this, "Button_WinMenu");
        Button_WinMenu->addClickEventListener([=](Ref*)
            {
                gotoInterFaceGame(this);
            });

        auto Button_WinNext = utils::findChild<ui::Button*>(this, "Button_WinNext");
        Button_WinNext->addClickEventListener([=](Ref*)
            {
                m_numOfLevel++;

                auto playLayer = PlayLayer::createScene(m_numOfLevel);

                Director::getInstance()->replaceScene(TransitionFade::create(0.2, playLayer));
            });

        if (m_Heart == 10)
        {
            auto _3star = utils::findChild<ui::ImageView*>(this, "Image_3Star");
            _3star->setVisible(true);
        }
        if (m_Heart > 5 && m_Heart < 10)
        {
            auto _2star = utils::findChild<ui::ImageView*>(this, "Image_2Star");
            _2star->setVisible(true);
        }
        if (m_Heart > 3 && m_Heart < 6)
        {
            auto _1star = utils::findChild<ui::ImageView*>(this, "Image_1Star");
            _1star->setVisible(true);
        }
        if (m_Heart > 0 && m_Heart < 4)
        {
            auto _0star = utils::findChild<ui::ImageView*>(this, "Image_0star");
            _0star->setVisible(true);
        }
    }
}

// plus20 minus100 minus120
void PlayLayer::updateGold(string _rq)
{
    if (_rq == "plus20")
    {
        m_gold = m_gold + 40;
    }
    if (_rq == "minus100")
    {
        m_gold = m_gold - 100;
    }
    if (_rq == "minus120")
    {
        m_gold = m_gold - 120;
    }
    createGoldAndHeartDisplay();
}

bool PlayLayer::onContactBegin(cocos2d::PhysicsContact& contact)
{
    PhysicsBody* a = contact.getShapeA()->getBody();
    PhysicsBody* b = contact.getShapeB()->getBody();
    // 1 đích
    // 2 quái
    // 3 quân đội

    if ((a->getCollisionBitmask() == 1 && b->getCollisionBitmask() == 2) ||
        (a->getCollisionBitmask() == 2 && b->getCollisionBitmask() == 1))
    {
        if (a->getCollisionBitmask() == 1) {
            if (a->getNode()) {
                //CCLOG("not do");
            }
        }
        if (b->getCollisionBitmask() == 2) {
            if (b->getNode()) {
                CCLOG("remove enemy");
                auto point = b->getPosition();
                
                for (int i = 0; i < m_EnemyArray.size(); i++)
                {
                    if (m_EnemyArray[i]->getEnemyCharacter()->getPosition() == point)
                    {
                        m_EnemyArray[i]->getEnemyCharacter()->removeFromParent();
                        m_EnemyArray[i]->getHealthBar()->removeFromParent();
                        m_EnemyArray.erase(m_EnemyArray.begin() + i);
                        m_movetoList.erase(m_movetoList.begin() + i);
                        if (m_Heart > 0)
                        {
                            m_Heart--;
                            if (m_Heart == 0)
                            {
                                //checkFinishLevel(1);
                            }
                        }                        
                        // show gold and heart into screens
                        createGoldAndHeartDisplay();
                    }
                }

            }
        }

    }

    return false;
}

