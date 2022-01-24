#include<iostream>
#include "ArcherTower.h"
#include "cocos2d.h"
using namespace std;

ArcherTower::ArcherTower(cocos2d::Point _curPoint)
{
	// B1 cài tọa độ
	// B2 tạo đối tượng lên tọa độ đấy
	setCurrentPosition(_curPoint);
	createArcherTowerSprite();

	for (int i = 0; i < 2; i++)
	{
		Army* army = new Army();
		army->createArcherArmySprite();
		m_ArcherArmy.push_back(army);
	}

	setPositionForArcherArmy();
}

void ArcherTower::setCurrentPosition(cocos2d::Point _point)
{
	m_curPosition = _point;
}

void ArcherTower::setCoin(int _coin)
{
	m_coin = _coin;
}

void ArcherTower::setPositionForArcherArmy()
{
	for (int i = 0; i < m_ArcherArmy.size(); i++)
	{
		m_ArcherArmy[i]->getArmyCharacter()->setPosition
		(
			m_ArcherTower->getPosition().x + 10*i - 10,
			m_ArcherTower->getPosition().y + m_ArcherTower->getContentSize().height/2 - 15
		);
	}
}

void ArcherTower::createArcherTowerSprite()
{
	m_ArcherTower = cocos2d::Sprite::create("Archer_tower/2.png");
	m_ArcherTower->setPosition(m_curPosition);
	m_ArcherTower->setScale(0.65);
	m_ArcherTower->setVisible(true);
}

Animate* ArcherTower::getArcherArmyAnimate()
{
	auto characterAnimation = Animation::create();
	characterAnimation->setDelayPerUnit(0.15f);
	characterAnimation->setLoops(-1);
	for (int i = 44; i < 51; i++)
	{
		characterAnimation->addSpriteFrame(Sprite::create("Archer_tower/" + to_string(i) + ".png")->getSpriteFrame());
	}
	Animate* animate = Animate::create(characterAnimation);
	return animate;
}

cocos2d::Sprite* ArcherTower::getArcherTowerSprite()
{
	return m_ArcherTower;
}

cocos2d::Sprite* ArcherTower::getArrowOfArcherTowerSprite()
{
	m_ArrowArcherTower = Sprite::create("Archer_tower/28.png");
	m_ArrowArcherTower->setPosition(m_ArcherTower->getPosition().x, m_ArcherTower->getPosition().y + m_ArcherTower->getContentSize().height / 2);
	m_ArrowArcherTower->setScale(0.2);

	return m_ArrowArcherTower;
}

cocos2d::Point ArcherTower::getCurPosition()
{
	return m_curPosition;
}

vector<Army*> ArcherTower::getArcherArmyVector()
{
	return m_ArcherArmy;
}

int ArcherTower::getCoin()
{
	return m_coin;
}
