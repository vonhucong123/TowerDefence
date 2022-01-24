#include "Enemy.h"
#include "Person.h"
#include <iostream>
#include "cocos2d.h"
#include "Data.h"
using namespace std;

Enemy::Enemy()
{
	loadEnemyData();
	setEnemySprite();
	characterAnimation(19);
	Person::setHealth(100);
	Person::createHeathPar();
}

Enemy::~Enemy()
{
	delete m_EnemyData;
	delete m_EnemySprite;
}
void Enemy::loadEnemyData()
{

	m_EnemyData->loadFileJson("Enemy.json");
	string _path, _enemyWalk;
	_path = m_EnemyData->getStringOfMember("Enemy", "Path");
	_enemyWalk = m_EnemyData->getStringOfMember("Enemy", "EnemyWalkName");

	// tạo đối tượng lên màn hình
	Person::setImagePath(_path + _enemyWalk);
	Person::createCharacter();
	setEnemySprite();
}

void Enemy::setEnemySprite()
{
	m_EnemySprite = Person::getCharacter();
}

Animate* Enemy::getEnemyDieSprite()
{
	string _path, _enemyDie;
	_path = m_EnemyData->getStringOfMember("Enemy", "Path");
	_enemyDie = m_EnemyData->getStringOfMember("Enemy", "EnemyDie");
	Person::setImagePath(_path + _enemyDie);
	
	return Person::characterDie(19);
}

Sprite* Enemy::getEnemyCharacter()
{
	return m_EnemySprite;
}
