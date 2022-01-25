#ifndef __PERSON_H__
#define __PERSON_H__

#include <cocos2d.h>
#include <iostream>
using namespace std;
USING_NS_CC;

class Person : public Layer
{
public:
	Person();
	~Person();
	void setHealth					(int _health);
	int	 getHealth();
	void setNewPoint				(int _x, int _y);
	void setFirstPoint				(int _x, int _y);
	void setImagePath				(string _imagePath);
	Point	getCurPoint();

	void createCharacter();
	void createHeathPar();
	void setHealthBar				(int _health);
	void characterMoveTo			(Point _point);
	Animate* characterDie				(int _numImage);
	void characterHurt();
	void characterAnimation			(int _numImage);
	cocos2d::Sprite*		getCharacter();
	cocos2d::PhysicsBody*	getPersonEdgeBox1();
	cocos2d::PhysicsBody*	getPersonEdgeBox2();
	cocos2d::ProgressTimer* getHealthBar();

protected:
	Point m_firstPoint;
	Point m_newPoint;
	Point m_curPoint;

	string m_imagePath;

	int					m_health;
	cocos2d::Sprite*	m_character;
	PhysicsBody*		m_edgeBox1;
	PhysicsBody*		m_edgeBox2;
	ProgressTimer*		m_healthBar;
	Animate*			m_characterDie;
};

#endif // __PERSON_H__