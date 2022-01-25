#include<iostream>
#include "StoneTower.h"
#include "cocos2d.h"
using namespace std;

StoneTower::StoneTower(cocos2d::Point _curPoint)
{
	// B1 cài tọa độ
	// B2 tạo đối tượng lên tọa độ đấy
	setCurrentPosition(_curPoint);
	createStoneTowerSprite();
	createheadStoneTowerLeft();
	createheadStoneTowerRight();
	createStone();
	createStoneBreak();
}

void StoneTower::setCurrentPosition(cocos2d::Point _point)
{
	m_curPosition = _point;
}

void StoneTower::setCoin(int _coin)
{
	m_coin = _coin;
}

void StoneTower::createStoneTowerSprite()
{
	m_StoneTower = cocos2d::Sprite::create("stone_tower/24.png");
	m_StoneTower->setPosition(m_curPosition);
	m_StoneTower->setScale(0.65);
	m_StoneTower->setVisible(true);
}

cocos2d::Sprite* StoneTower::getStoneTowerSprite()
{
	return m_StoneTower;
}

cocos2d::Point StoneTower::getCurPosition()
{
	return m_curPosition;
}

int StoneTower::getCoin()
{
	return m_coin;
}

void StoneTower::createStone()
{
	m_stone = cocos2d::Sprite::create("stone_tower/50.png");
	m_stone->setScale(0.4);
	m_stone->setPosition(
		m_headStoneTowerLeft->getPosition().x + 25,
		m_headStoneTowerLeft->getPosition().y + m_headStoneTowerLeft->getContentSize().height / 2
	);
}

void StoneTower::createheadStoneTowerRight()
{
	m_headStoneTowerRight = cocos2d::Sprite::create("stone_tower/28.png");
	m_headStoneTowerRight->setScale(0.65);
	m_headStoneTowerRight->setPosition(m_StoneTower->getPosition().x + 20, 
		m_StoneTower->getPosition().y + m_StoneTower->getContentSize().height/4);
}

void StoneTower::createheadStoneTowerLeft()
{
	m_headStoneTowerLeft = cocos2d::Sprite::create("stone_tower/28.png");
	m_headStoneTowerLeft->setScale(0.65);
	m_headStoneTowerLeft->setPosition(m_StoneTower->getPosition().x - 30,
		m_StoneTower->getPosition().y + m_StoneTower->getContentSize().height / 4);
}

cocos2d::Sprite* StoneTower::getHeadStoneTowerRightSprite()
{
	return m_headStoneTowerRight;
}

cocos2d::Sprite* StoneTower::getHeadStoneTowerLeftSprite()
{
	return m_headStoneTowerLeft;
}

cocos2d::Sprite* StoneTower::getStoneSprite()
{
	return m_stone;
}

cocos2d::Sprite* StoneTower::getStoneBreakSprite()
{
	return m_stoneBreak;
}

cocos2d::Sequence* StoneTower::getHeadStoneTowerLeftSequence()
{
	// HeadStone up and down
	cocos2d::MoveTo* moveup = cocos2d::MoveTo::create(0.2,
		cocos2d::Point
		(
			m_headStoneTowerLeft->getPosition().x,
			m_headStoneTowerLeft->getPosition().y + m_headStoneTowerLeft->getContentSize().height / 3
			));
	cocos2d::MoveTo* moveDown = cocos2d::MoveTo::create(0.8,
		cocos2d::Point
		(
			m_headStoneTowerLeft->getPosition().x,
			m_headStoneTowerLeft->getPosition().y
		));

	//cocos2d::Repeat::create();
	cocos2d::Sequence* seq = cocos2d::Sequence::create(moveup, moveDown, cocos2d::DelayTime::create(0.5), nullptr);

	return seq;
}

cocos2d::Sequence* StoneTower::getHeadStoneTowerRightSequence()
{
	// HeadStone up and down
	cocos2d::MoveTo* moveup = cocos2d::MoveTo::create(0.2,
		cocos2d::Point
		(
			m_headStoneTowerRight->getPosition().x,
			m_headStoneTowerRight->getPosition().y + m_headStoneTowerRight->getContentSize().height / 3
		));
	cocos2d::MoveTo* moveDown = cocos2d::MoveTo::create(0.8,
		cocos2d::Point
		(
			m_headStoneTowerRight->getPosition().x,
			m_headStoneTowerRight->getPosition().y
		));

	//cocos2d::Repeat::create();
	// time total = 0.2 0.8 0.5 = 1.5
	cocos2d::Sequence* seq = cocos2d::Sequence::create(moveup, moveDown, cocos2d::DelayTime::create(0.5), nullptr);

	return seq;
}

cocos2d::Sequence* StoneTower::getStoneFlyUpSequence()
{
	// time total 0.2 + 0.5 + 0.2 + 0.1 = 1s + 0.5 delay for next clock

	cocos2d::MoveTo* actionAway = cocos2d::MoveTo::create(0.2, cocos2d::Vec2(m_stone->getPosition().x, m_stone->getPosition().y + 50));

	cocos2d::MoveTo* actionComeback = cocos2d::MoveTo::create(0.2, cocos2d::Vec2(m_stone->getPosition().x, m_stone->getPosition().y));

	cocos2d::Sequence* seq = cocos2d::Sequence::create(actionAway, cocos2d::FadeOut::create(0.5), actionComeback, cocos2d::FadeIn::create(0.1), cocos2d::DelayTime::create(0.5), nullptr);

	return seq;
}
cocos2d::Sequence* StoneTower::getStoneFlyDownSequence(cocos2d::Point _point)
{
	// xuất phát từ trên quân địch
	// di chuyển xuống đối tượng
	// viên đá vỡ và biến mất từ từ.

	m_stoneBreak->setPosition(cocos2d::Vec2(_point.x, _point.y + 50));

	cocos2d::MoveTo* action = cocos2d::MoveTo::create(0.2, cocos2d::Vec2(_point.x, _point.y));

	cocos2d::Animate* animate = getStoneBreakAnimate(); // 0.7

	cocos2d::Sequence* seq = cocos2d::Sequence::create(cocos2d::DelayTime::create(0.6), action, animate, nullptr);

	return seq;
}
cocos2d::Animate* StoneTower::getStoneBreakAnimate()
{
	auto characterAnimation = cocos2d::Animation::create();
	characterAnimation->setDelayPerUnit(0.1f);
	characterAnimation->addSpriteFrame(cocos2d::Sprite::create("stone_tower/29.png")->getSpriteFrame());
	characterAnimation->addSpriteFrame(cocos2d::Sprite::create("stone_tower/30.png")->getSpriteFrame());
	characterAnimation->addSpriteFrame(cocos2d::Sprite::create("stone_tower/31.png")->getSpriteFrame());
	characterAnimation->addSpriteFrame(cocos2d::Sprite::create("stone_tower/32.png")->getSpriteFrame());
	characterAnimation->addSpriteFrame(cocos2d::Sprite::create("stone_tower/33.png")->getSpriteFrame());
	characterAnimation->addSpriteFrame(cocos2d::Sprite::create("stone_tower/34.png")->getSpriteFrame());
	characterAnimation->addSpriteFrame(cocos2d::Sprite::create("stone_tower/x.png")->getSpriteFrame());

	cocos2d::Animate* animate = cocos2d::Animate::create(characterAnimation);

	return animate;
}

void StoneTower::createStoneBreak()
{
	m_stoneBreak = cocos2d::Sprite::create("stone_tower/29.png");
	m_stoneBreak->setPosition(-10, -10);
	m_stoneBreak->setVisible(false);
	m_stoneBreak->setScale(0.5);
}



