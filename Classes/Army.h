#ifndef __ARMY_H__
#define __ARMY_H__

#include "Person.h"
#include "Data.h"
#include "cocos2d.h"
#include <iostream>
using namespace std;


class Army : public Person
{
public:
	Army();
	void loadArmyData();
	void createArcherArmySprite();
	void setArmySprite();
	void setDieAction();
	Sprite* getArmyCharacter();
	Animate* getArmyCharacterDie(Point _point);

private:
	GameData* m_ArmyData = new GameData();
	Sprite* m_ArmySprite;
};

#endif 