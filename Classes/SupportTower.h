#ifndef __SUPPORT_H__
#define __SUPPORT_H__

#include "cocos2d.h"
#include "Denifition.h"
#include "Army.h"
#include <iostream>
#include <vector>
using namespace std;

class SupportTower
{
public:
	SupportTower(cocos2d::Point _curPoint);
	void setCurrentPosition(cocos2d::Point _point);
	void setCoin(int _coin);
	void setIndexFlag(int _idx);
	void createSupportTowerSprite();
	void createSupportTowerFlagSprite();
	void createFlagSprite(cocos2d::Point _point);
	cocos2d::Sprite*	getSupportTowerSprite();
	cocos2d::Sprite*	getFlagSprite();
	cocos2d::Point		getCurPosition();
	int					getIdxFlag();
	int					getCoin();
	~SupportTower();

	vector<Army*> getArmyList();

private:
	cocos2d::Point		m_curPosition;			// lưu tọa độ hiện tại
	int m_coin =		SUPPORT_TOWER_COIN;		// số tiền mua
	cocos2d::Sprite*	m_supportTower;		
	vector<Army*>		m_ArmyList;				// 3 lính
	cocos2d::Sprite*	m_flag;	
	int				m_idxFlag;
};

#endif 