#ifndef __PLAYLAYER_SCENE_H__
#define __PLAYLAYER_SCENE_H__

#include "Data.h"
#include "cocos2d.h"
#include "Army.h"
#include "Enemy.h"
#include <vector>
#include "SupportTower.h"
#include "ArcherTower.h"
#include "StoneTower.h"
#include "MagicTower.h"

class PlayLayer : public cocos2d::Layer
{
public:
    static cocos2d::Scene* createScene(int _level);

    virtual bool init();

    void initScene();

    void initLevel();

    void initButton();

    void initEnemy(float dt);

    void initTimerCreateEnemyWare();

    void createGoldAndHeartDisplay();

    // cứ mỗi giây sẽ kiểm tra va chạm cho mọi đối tượng
    void initScheduleCheckWar(float dt); 

    void setFlagForSupportTower (cocos2d::Point _point);

    void delFlagForSupportTower (int idx);

    bool buildSupportTower      (cocos2d::Point _point);

    bool buildArcherTower       (cocos2d::Point _point);

    bool buildMagicTower        (cocos2d::Point _point);

    bool buildStoneTower        (cocos2d::Point _point);

    void setLineForEmemy();

    bool onTouchBegan           (cocos2d::Touch* touch, cocos2d::Event* event);

    void onTouchMove            (cocos2d::Touch* touch, cocos2d::Event* event);

    void onTouchEnded           (cocos2d::Touch* touch, cocos2d::Event* event);

    void setPhysicsWorld        (cocos2d::PhysicsWorld* _world);

    void gotoInterFaceGame      (cocos2d::Ref* sender);

    void upgradeTower           (int _type);

    void updateObjectHealth     (float dt);

    void checkDistanceArcherTower(float dt);

    void checkDistanceMagicTower();

    void checkDistanceToneTower();

    void checkEnemyAndArmy      (float dt);

    void checkTimerForWare();

    void checkFinishLevel       (float dt);

    void updateGold(string _rq);

    bool onContactBegin         (cocos2d::PhysicsContact& contact);
    
    void menuCloseCallback      (cocos2d::Ref* pSender);

    CREATE_FUNC(PlayLayer);

private:
    int                     m_ware              = 0;       // sau mỗi lần tạo ware thì sẽ tăng lên 1
    int                     m_Heart             = 10;
    int                     m_gold              = 200;
    int                     m_numOfLevel;
    cocos2d::PhysicsWorld*  world;
    GameData*               m_Level             = new GameData();
    vector<int>             m_numEnemy;                             // lưu số lượng quái mỗi ware 
    vector<Point>           m_LineForEnemy;                    // lưu đường đi
    vector<Enemy*>          m_EnemyArray;
    vector<vector<MoveTo*>> m_movetoList;                // lưu hoạt động đi của mỗi đối tượng army
    vector<SupportTower*>   m_SupportTowerList;           // danh sách supportTower;
    vector<Sprite*>         m_flagOfSupportTowerList;
    vector<ArcherTower*>    m_ArcherTowerList;              // danh sach ArcherTower
    vector<StoneTower*>     m_StoneTowerList;                // danh sachs Stone Tower
    vector<MagicTower*>     m_MagicTowerList;
    ProgressTimer*          m_timerWare;                       // check time for next ware;
};

#endif // 
