#pragma once
#include <iostream>
#include <vector>
#include <map>
#include "speaker.h"
using namespace std;

class speechManager
{
public:
	//构造函数
	speechManager();


	//菜单
	void showMenu();


	//退出比赛程序
	void exitSystem();


	//初始化容器
	void initSpeach();
	

	//创建选手
	void createSpeaker();


	//创建比赛入口
	void startSpeech();


	//抽签
	void speechDraw();
	
	//析构函数
	~speechManager();

	//比赛选手
	vector<int> v0;
	//第一轮
	vector<int> v1;
	//第二轮
	vector<int> v2;
	//编号何具体选手姓名的容器
	map<int, speaker> m;
	//比赛轮数
	int m_index;
};

