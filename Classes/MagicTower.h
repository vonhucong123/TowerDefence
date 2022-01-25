#ifndef __MAGIC_H__
#define __MAGIC_H__

#include "cocos2d.h"
#include "Denifition.h"
#include <iostream>
#include <vector>
using namespace std;

class MagicTower
{
public:
	MagicTower(cocos2d::Point _curPoint);
	void setCurrentPosition(cocos2d::Point _point);
	void setCoin(int _coin);
	void createMagicTowerSprite();
	void createHeadMagicTowerSprite();
	void createMagicTowerAction();
	cocos2d::Sprite* getMagicTowerSprite();
	cocos2d::Sprite* getHeadMagicTowerSprite();
	cocos2d::Sprite* getMagicTowerElectricSprite();
	cocos2d::Animate* getMagicTowerAnimate();
	cocos2d::Point getCurPosition();
	int getCoin();

private:
	cocos2d::Point m_curPosition;			// lưu tọa độ hiện tại
	int m_coin = MAGIC_TOWER_COIN;		// số tiền mua
	cocos2d::Sprite* m_MagicTower;
	cocos2d::Sprite* m_headMagicTower;
	cocos2d::Sprite* m_MagicTowerElectricSprite;
	cocos2d::Animate* m_MagicTowerAction;	// bắn tia sét	
};

#endif 