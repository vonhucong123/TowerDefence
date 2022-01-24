#ifndef __ARCHER_H__
#define __ARCHER_H__

#include "cocos2d.h"
#include "Denifition.h"
#include "Army.h"
#include <iostream>
#include <vector>
using namespace std;

class ArcherTower
{
public:
	ArcherTower(cocos2d::Point _curPoint);
	void setCurrentPosition(cocos2d::Point _point);
	void setCoin(int _coin);
	void setPositionForArcherArmy();
	void createArcherTowerSprite();
	Animate* getArcherArmyAnimate();
	cocos2d::Sprite* getArcherTowerSprite();
	cocos2d::Sprite* getArrowOfArcherTowerSprite();
	cocos2d::Point getCurPosition();
	vector<Army*>	getArcherArmyVector();
	int getCoin();

private:
	cocos2d::Point		m_curPosition;			// lưu tọa độ hiện tại
	int m_coin =		ARCHER_TOWER_COIN;			// số tiền mua
	cocos2d::Sprite*	m_ArcherTower;			// sprite để hiển thị
	cocos2d::Sprite*	m_ArrowArcherTower;
	vector<Army*>		m_ArcherArmy;
};

#endif 