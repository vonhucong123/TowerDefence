#include<iostream>
#include "MagicTower.h"
#include "cocos2d.h"
using namespace std;

MagicTower::MagicTower(cocos2d::Point _curPoint)
{
	// B1 cài tọa độ
	// B2 tạo đối tượng lên tọa độ đấy
	setCurrentPosition(_curPoint);
	createMagicTowerSprite();
	createHeadMagicTowerSprite();
	createMagicTowerAction();
}

void MagicTower::setCurrentPosition(cocos2d::Point _point)
{
	m_curPosition = _point;
}

void MagicTower::setCoin(int _coin)
{
	m_coin = _coin;
}

void MagicTower::createMagicTowerSprite()
{
	m_MagicTower = cocos2d::Sprite::create("Magic_tower/2.png");
	m_MagicTower->setPosition(m_curPosition);
	m_MagicTower->setScale(0.65);
	m_MagicTower->setVisible(true);
}

void MagicTower::createHeadMagicTowerSprite()
{
	m_headMagicTower = cocos2d::Sprite::create("Magic_tower/1.png");
	m_headMagicTower->setPosition(
		m_MagicTower->getPosition().x - 8,
		m_MagicTower->getPosition().y + m_MagicTower->getContentSize().height / 2 - 10);
	m_headMagicTower->setScale(0.7);
}

void MagicTower::createMagicTowerAction()
{
	auto _magicTowerAction = cocos2d::Animation::create();
	_magicTowerAction->setDelayPerUnit(0.5f);

	_magicTowerAction->addSpriteFrame(cocos2d::Sprite::create("Magic_tower/19.png")->getSpriteFrame());
	_magicTowerAction->addSpriteFrame(cocos2d::Sprite::create("Magic_tower/20.png")->getSpriteFrame());

	m_MagicTowerAction = cocos2d::Animate::create(_magicTowerAction);
}

cocos2d::Sprite* MagicTower::getMagicTowerSprite()
{
	return m_MagicTower;
}

cocos2d::Sprite* MagicTower::getHeadMagicTowerSprite()
{
	return m_headMagicTower;
}

cocos2d::Animate* MagicTower::getMagicTowerAnimate()
{
	return m_MagicTowerAction;
}

cocos2d::Point MagicTower::getCurPosition()
{
	return m_curPosition;
}

int MagicTower::getCoin()
{
	return m_coin;
}

