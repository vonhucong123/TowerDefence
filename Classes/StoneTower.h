#ifndef __STONE_H__
#define __STONE_H__

#include "cocos2d.h"
#include "Denifition.h"
#include <iostream>
#include <vector>
using namespace std;

class StoneTower
{
public:
	StoneTower(cocos2d::Point _curPoint);
	void setCurrentPosition(cocos2d::Point _point);
	void setCoin(int _coin);
	void createStoneTowerSprite();
	void createheadStoneTowerRight();
	void createheadStoneTowerLeft();
	void createStone();
	void createStoneBreak();
	cocos2d::Sprite* getHeadStoneTowerRightSprite();
	cocos2d::Sprite* getHeadStoneTowerLeftSprite();
	cocos2d::Sprite* getStoneSprite();
	cocos2d::Sprite* getStoneBreakSprite();
	cocos2d::Sprite* getStoneTowerSprite();
	cocos2d::Point getCurPosition();
	cocos2d::Sequence* getHeadStoneTowerLeftSequence();
	cocos2d::Sequence* getHeadStoneTowerRightSequence();
	cocos2d::Sequence* getStoneFlyUpSequence();
	cocos2d::Sequence* getStoneFlyDownSequence(cocos2d::Point _point);
	cocos2d::Animate* getStoneBreakAnimate();
	int getCoin();

private:
	cocos2d::Point m_curPosition;			// lưu tọa độ hiện tại
	int m_coin = STONE_TOWER_COIN;		// số tiền mua
	cocos2d::Sprite* m_StoneTower;
	cocos2d::Sprite* m_headStoneTowerRight;
	cocos2d::Sprite* m_headStoneTowerLeft;
	cocos2d::Sprite* m_stone;
	cocos2d::Sprite* m_stoneBreak;
};

#endif 