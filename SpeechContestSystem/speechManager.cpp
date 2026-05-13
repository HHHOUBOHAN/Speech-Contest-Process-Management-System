#define _CRT_SECURE_NO_WARNINGS 1
#include <iostream>
#include <algorithm>
#include "speechManager.h"
#include "speaker.h"
using namespace std;

//构造函数
speechManager::speechManager()
{

}


//菜单
void speechManager::showMenu()
{
	cout << "********************************************" << endl;
	cout << "************* 欢迎参加演讲比赛  ************" << endl;
	cout << "************* 1. 开始演讲比赛  *************" << endl;
	cout << "************* 2. 查看往届记录  *************" << endl;
	cout << "************* 3. 清空比赛记录  *************" << endl;
	cout << "************* 0. 退出比赛程序  *************" << endl;
	cout << "********************************************" << endl;
	cout << endl;
}


//退出比赛程序
void speechManager::exitSystem()
{
	cout << "欢迎下次使用" << endl;
	system("cls");
	exit(0);
}

//创建对象
void speechManager::createSpeaker()
{
	string nameSeed = "ABCDEFGHIJKL";
	for (int i = 0; i < nameSeed.size(); i++)
	{
		string name = "选手";
		name += nameSeed[i];
		speaker s;
		s.m_name = name;

		//初始化两轮成绩为0
		for (int j = 0; j < 2; j++)
		{
			s.m_score[j] = 0;
		}

		this->v0.push_back(10001 + i);
		this->m.insert(make_pair(10001+i,s));
	}
}

//开始比赛
void speechManager::startSpeech()
{
	this->createSpeaker();
	this->m_index++;
	this->speechDraw();//抽签
	//比赛
	//显示晋级结果
	


	//抽签
	//比赛

	//显示最终结果

	//保存分数




}
//抽签
void speechManager::speechDraw()
{

	cout << "第" << this->m_index << "轮比赛选手正在抽签" << endl;
	
	cout << "抽签后的演讲顺序如下:" << endl;
	if (m_index == 1)
	{
		random_shuffle(v1.begin(), v1.end());
		for (vector<int>::iterator it = v1.begin(); it != v1.end(); it++)
		{
			cout << *it << " ";
		}
	}

	else if(m_index==2)
	{
		random_shuffle(v2.begin(), v2.end());
		for (vector<int>::iterator it = v2.begin(); it != v2.end(); it++)
		{
			cout << *it << " ";
		}
	}
	cout << "----------------------" << endl;
	system("pause");
	cout << endl;
}


//容器置空
void speechManager::initSpeach()
{
	this->v0.clear();
	this->v1.clear();
	this->v2.clear();
	this->m.clear();

	this->m_index = 0;
}


//析构函数
speechManager::~speechManager()
{

}
 