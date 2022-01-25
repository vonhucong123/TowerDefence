#include "Person.h"
#include <iostream>
#include "cocos2d.h"
using namespace std;

Person::Person()
{

}

Person::~Person()
{
    //delete m_character;
    //delete m_edgeBox1;
    //delete m_edgeBox2;
   // delete m_healthBar;
}

void Person::setHealth(int _health)
{
	m_health = _health;
}

int Person::getHealth()
{
	return m_health;
}

void Person::setNewPoint(int _x, int _y)
{
    m_newPoint = Point(_x, _y);
}

void Person::setFirstPoint(int _x, int _y)
{
    m_firstPoint = Point(_x, _y);
}

void Person::setImagePath(string _imagePath)
{
    m_imagePath = _imagePath;
}

Point Person::getCurPoint()
{
    return m_curPoint;
}

void Person::createCharacter()
{
	// create sprite and PhysicBox
    m_character = Sprite::create(m_imagePath+ "1.png");
    m_character->setPosition(m_firstPoint);
    m_character->setScale(0.2);
}

void Person::createHeathPar()
{
    m_healthBar = ProgressTimer::create(Sprite::create("td-gui/load_bar/load_bar_1.png"));
    m_healthBar->setType(ProgressTimer::Type::BAR);
    m_healthBar->setMidpoint(Vec2(0.0f, 0.5f));
    m_healthBar->setBarChangeRate(Vec2(1.0f, 0.0f));
    m_healthBar->setPercentage(100);
    m_healthBar->setScale(0.04);
    m_healthBar->setPosition(m_character->getPosition().x, m_character->getPosition().y + m_character->getContentSize().height/2);
}

void Person::setHealthBar(int _health)
{
    m_healthBar->setPercentage(_health);
    setHealth(_health);
}

void Person::characterMoveTo(Point _point)
{    
    m_character->runAction(MoveTo::create(1.0f, _point));
}

Animate* Person::characterDie(int _numImage)
{
    auto characterDieAnimation = Animation::create();

    characterDieAnimation->setDelayPerUnit(0.1f);     // 0.15s next image
    //characterDieAnimation->setLoops(-1);               // loop animation
    for (int i = 1; i < _numImage; i++)
    {
        string _imagePath = m_imagePath + to_string(i) + ".png";
        characterDieAnimation->addSpriteFrame(Sprite::create(_imagePath)->getSpriteFrame());

    }
    // khởi tạo hoạt động lên anime
    Animate* animate = Animate::create(characterDieAnimation);
    return animate;
}

void Person::characterHurt()
{
}

void Person::characterAnimation(int _numImage)
{
    auto characterAnimation = Animation::create();
    characterAnimation->setDelayPerUnit(0.15f);     // 0.15s next image
    characterAnimation->setLoops(-1);               // loop animation
    for (int i = 1; i < _numImage; i++)
    {
        string _imagePath = m_imagePath + to_string(i) + ".png";
        characterAnimation->addSpriteFrame(Sprite::create(_imagePath)->getSpriteFrame());

    }
    // khởi tạo hoạt động lên anime
    Animate* animate = Animate::create(characterAnimation);
    animate->setTag(100);
    m_character->runAction(animate);
}


cocos2d::Sprite* Person::getCharacter()
{
    return m_character;
}

cocos2d::PhysicsBody* Person::getPersonEdgeBox1()
{
    return m_edgeBox1;
}

cocos2d::PhysicsBody* Person::getPersonEdgeBox2()
{
    return m_edgeBox2;
}

cocos2d::ProgressTimer* Person::getHealthBar()
{
    return m_healthBar;
}
