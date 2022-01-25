#ifndef __ENEMY_H__
#define __ENEMY_H__

#include "Person.h"
#include "Data.h"
#include "cocos2d.h"
#include "Denifition.h"
#include <iostream>
using namespace std;


class Enemy : public Person
{
public:
	Enemy();
	~Enemy();
	void loadEnemyData();
	void setEnemySprite();
	Animate* getEnemyDieSprite();
	Sprite* getEnemyCharacter();

private:
	GameData*	m_EnemyData = new GameData();
	Sprite*		m_EnemySprite;		
};

#endif 