#ifndef __DATA_H__
#define __DATA_H__

#include <iostream>
#include "rapidjson/document.h"
#include "cocos2d.h"
#include <vector>
using namespace std;
using namespace rapidjson;

class GameData
{
public:
	GameData();
	void setUserName(string &_userName);
	void setPassWord(string &_pass);
	string getUserName();
	string getPassWord();

	void saveAccout();
	bool isAccoutAvariable();
	void loadFileJson(string _rq);
	string getStringOfMember(string _member1, string _object);
	int getIntOfMember(string _member1, string _object);
	void getAllPoint(string _member1, string _object);


private:
	string m_userName = "1";
	string m_passWord = "1";
	Document m_document;
	vector<cocos2d::Point>* m_allPoint;
};

#endif
