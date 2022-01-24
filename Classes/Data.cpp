#include "Data.h"
#include <iostream>
#include "rapidjson/document.h"
#include "rapidjson/filewritestream.h"
#include <rapidjson/writer.h>
#include "rapidjson/filereadstream.h"
#include "cocos2d.h"
using namespace rapidjson;
using namespace std;

GameData::GameData()
{
}

void GameData::setUserName(string &_userName)
{
	m_userName = _userName;
}

void GameData::setPassWord(string &_pass)
{
	m_passWord = _pass;
}

string GameData::getUserName()
{
	return m_userName;
}

string GameData::getPassWord()
{
	return m_passWord;
}

void GameData::saveAccout()
{
	if (!isAccoutAvariable())
	{
		// save accout;
	}
}

// check username and password
bool GameData::isAccoutAvariable()
{
	std::string _userName;
	std::string _password;
	_userName = getStringOfMember("ACCOUT", "Name");
	_password = getStringOfMember("ACCOUT", "Password");
	if (m_userName == _userName && m_passWord == _password)
	{
		return true;
	}
	return false;
}

// load data from file json
void GameData::loadFileJson(string _rq)
{
	std::string str = cocos2d::FileUtils::getInstance()->getStringFromFile("userData/"+_rq);
	CCLOG("file content: %s", str.c_str());
	m_document.Parse(str.c_str());
}

string GameData::getStringOfMember(string _member1, string _object)
{
	if (m_document.HasMember(_member1.c_str()))
	{
		const rapidjson::Value& employeeArray = m_document[_member1.c_str()];
		assert(employeeArray.IsArray());

		for (rapidjson::SizeType i = 0; i < employeeArray.Size(); i++)
		{
			const rapidjson::Value& atomicObject = employeeArray[i];
			if (atomicObject.HasMember(_object.c_str())) {
				const rapidjson::Value& name = atomicObject[_object.c_str()];
				return cocos2d::Value(name.GetString()).asString();

			}
		}
	}
}

int GameData::getIntOfMember(string _member1, string _object)
{
	if (m_document.HasMember(_member1.c_str()))
	{
		const rapidjson::Value& employeeArray = m_document[_member1.c_str()];
		assert(employeeArray.IsArray());

		for (rapidjson::SizeType i = 0; i < employeeArray.Size(); i++)
		{
			const rapidjson::Value& atomicObject = employeeArray[i];
			if (atomicObject.HasMember(_object.c_str())) {
				const rapidjson::Value& name = atomicObject[_object.c_str()];
				return cocos2d::Value(name.GetInt()).asInt();

			}
		}
	}
}

void GameData::getAllPoint(string _member1, string _object)
{

	if (m_document.HasMember(_member1.c_str()))
	{
		const rapidjson::Value& employeeArray = m_document[_member1.c_str()];
		assert(employeeArray.IsArray());

		for (rapidjson::SizeType i = 0; i < employeeArray.Size(); i++)
		{
			const rapidjson::Value& atomicObject = employeeArray[i];
			if (atomicObject.HasMember(_object.c_str())) {
				const rapidjson::Value& name = atomicObject[_object.c_str()];

			}
		}
	}
}

