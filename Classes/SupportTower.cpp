#include<iostream>
#include "SupportTower.h"
#include "cocos2d.h"
using namespace std;

SupportTower::SupportTower(cocos2d::Point _curPoint)
{
	// B1 cài tọa độ
	// B2 tạo đối tượng lên tọa độ đấy
	setIndexFlag(-1);
	setCurrentPosition(_curPoint);
	createSupportTowerSprite();
	createSupportTowerFlagSprite();
}

void SupportTower::setCurrentPosition(cocos2d::Point _point)
{
	m_curPosition = _point;
}

void SupportTower::setCoin(int _coin)
{
	m_coin = _coin;
}

void SupportTower::setIndexFlag(int _idx)
{
	m_idxFlag = _idx;
}

void SupportTower::createSupportTowerSprite()
{
	m_supportTower = cocos2d::Sprite::create("support_tower/1.png");
	m_supportTower->setPosition(m_curPosition);
	m_supportTower->setScale(0.65);
	m_supportTower->setVisible(true);

	for (int i = 0; i < 3; i++)
	{
		Army* _army = new Army();
		_army->getArmyCharacter()->setPosition
		(Point(m_curPosition.x + m_supportTower->getContentSize().width/4 + 6 * i,
			m_curPosition.y - m_supportTower->getContentSize().height/4 ));
		_army->getArmyCharacter()->setScale(0.2);
		m_ArmyList.push_back(_army);
	}
}

void SupportTower::createSupportTowerFlagSprite()
{
	m_flag = cocos2d::Sprite::create("support_tower/18.png");
	m_flag->retain();
	//m_flag->release();
	if (m_flag) {
		m_flag->setPosition(m_curPosition);
		m_flag->setScale(0.5);
		m_flag->setName("SupportTowerFlagSprite");
	}
}

void SupportTower::createFlagSprite(cocos2d::Point _point)
{
	m_flag = Sprite::create("support_tower/18.png");
	m_flag->setPosition(_point);
	m_flag->setScale(0.5);
	m_flag->retain();
}

cocos2d::Sprite* SupportTower::getSupportTowerSprite()
{
	return m_supportTower;
}

cocos2d::Sprite* SupportTower::getFlagSprite()
{
	return m_flag;
}

cocos2d::Point SupportTower::getCurPosition()
{
	return m_curPosition;
}

int SupportTower::getIdxFlag()
{
	return m_idxFlag;
}

int SupportTower::getCoin()
{
	return m_coin;
}

SupportTower::~SupportTower()
{
}

vector<Army*> SupportTower::getArmyList()
{
	return m_ArmyList;
}
