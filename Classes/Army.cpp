#include "Army.h"
#include "Person.h"
#include <iostream>
#include "cocos2d.h"
#include "Data.h"
#include "Denifition.h"
using namespace std;

Army::Army()
{
	loadArmyData();
	Person::setHealth(100);
	Person::createHeathPar();
}

void Army::loadArmyData()
{
	
	m_ArmyData->loadFileJson("Army.json");
	string _path, _armyWalk;
	_path = m_ArmyData->getStringOfMember("Army", "Path");
	_armyWalk = m_ArmyData->getStringOfMember("Army", "ArmyWalkName");

	// tạo đối tượng lên màn hình
	Person::setImagePath(_path + _armyWalk);
	Person::createCharacter();
	setArmySprite();
}

// create character for Archer Tower
void Army::createArcherArmySprite()
{
	auto army = Sprite::create("Archer_tower/44.png");

	m_ArmySprite = army;
}

void Army::setArmySprite()
{
	m_ArmySprite = Person::getCharacter();
}

Sprite* Army::getArmyCharacter()
{
	return m_ArmySprite;
}

Animate* Army::getArmyCharacterDie(Point _point)
{
	string _path, _armyAttack;
	_path = m_ArmyData->getStringOfMember("Army", "Path");
	_armyAttack = m_ArmyData->getStringOfMember("Army", "ArmyAttack");

	Person::setImagePath(_path + _armyAttack);
	Person::createCharacter();
	setArmySprite();
	
	return characterDie(10);
}
