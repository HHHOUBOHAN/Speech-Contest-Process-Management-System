#define _CRT_SECURE_NO_WARNINGS 1
#include <iostream>
#include <fstream>
#include <algorithm>
#include <numeric>
#include <deque>
#include <vector>
#include "speechManager.h"
#include "speaker.h"
using namespace std;

//构造函数
speechManager::speechManager()
{
	this->initSpeach();

	this->loadRecord();
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
	//抽签
	this->speechDraw(); 
	//比赛
	this->speechContest();
	//显示晋级结果
	this->showScore();
	this->m_index++;
	//抽签
	this->speechDraw();
	//比赛
	this->speechContest();
	//显示最终结果
	this->showScore();
	//保存分数
	this->saveRecord();
}
//抽签
void speechManager::speechDraw()
{

	cout << "第" << this->m_index << "轮比赛选手正在抽签" << endl;
	
	cout << "抽签后的演讲顺序如下:" << endl;
	if (m_index == 1)
	{
		random_shuffle(v0.begin(), v0.end());
		for (vector<int>::iterator it = v0.begin(); it != v0.end(); it++)
		{
			cout << *it << " ";
		}
		cout << endl;
	}

	else if(m_index==2)
	{
		random_shuffle(v2.begin(), v2.end());
		for (vector<int>::iterator it = v2.begin(); it != v2.end(); it++)
		{
			cout << *it << " ";
		}
		cout << endl;
	}
	cout << "----------------------" << endl;
	system("pause");
	cout << endl;
}
void speechManager::speechContest()
{
	 
	cout << "第" << this->m_index << "轮比赛开始" << endl;

	multimap<double, int, greater<double>> mul;

	int num = 0;


	//这个要提前开辟空间
	
	vector<int> vc;
	if (m_index == 1)
	{
		v1 = v0;
		vc.resize(12);
		vc = v1;
	}
	else
	{

		vc.resize(6);
		vc = v2;
	}
	 

	for (vector<int>::iterator it = vc.begin(); it!=vc.end(); it++)
	{
		num++;

		deque<double> d;
		//打分
		for (int i = 0; i < 10; i++)
		{
			double score = (rand() % 401 + 600) / 10.0;//rand() % 401  产生0~400的数 最后+600 除10 范围就是60.0-100.0
			d.push_back(score);

		}
		/*cout << *it << "打分如下:" << endl;

		for (deque<double>::iterator dit = d.begin(); dit != d.end(); dit++)
		{
			cout << *dit << " ";
		}
		cout << endl;*/
	    //排序  去掉最高最低  取平均
		sort(d.begin(), d.end(), greater<double>());
		d.pop_front();
		d.pop_back();
		double sum = accumulate(d.begin(), d.end(), 0.0); // 0.0f → float 类型0.0 → double 类型

		//更新speak 的 score
		m[*it].m_score[m_index - 1] = sum;
		mul.insert(make_pair(sum, *it));//插入加make_pair

		if (num % 6 == 0)
		{
			cout << "第" << num / 6 << "组比赛名次" << endl;
			int count = 0;

			for (multimap<double, int, greater<double>>::iterator bit = mul.begin(); bit != mul.end() && count < 3; bit++, count++)
			{
				cout <<"姓名" <<m[bit->second].m_name<< " 编号" << bit->second << " 成绩" << bit->first <<"排名"<<count+1<< endl;
				//插入
				if (m_index == 1)
				{
					v2.push_back(bit->second);
				}
				else
				{
					Victory.push_back(bit->second);
				}
			}
			//***清理mul内部数据  进行下一组
			mul.clear();
			cout << endl;
		}
		
	}
	cout << this->m_index << "轮比赛已经over" << endl;
	system("pause");
}

//显示比赛结果
void speechManager::showScore()
{
	cout << "第" << this->m_index << "晋级结果如下:" << endl;
	if (m_index == 1)
	{
		
		for (vector<int>::iterator it = v2.begin(); it != v2.end(); it++)
		{
			cout << *it << " ";
		}
		cout << endl;
	}
	else
	{
		for (vector<int>::iterator it = Victory.begin(); it != Victory.end(); it++)
		{
			cout << *it << " ";
		}
		cout << endl;
	}
}
//保存比赛记录
void speechManager::saveRecord()
{
	ofstream ofs;
	ofs.open("speech.csv",ios::out|ios::app);
	//写入
	for (vector<int>::iterator it = Victory.begin(); it != Victory.end(); it++)
	{
		ofs << *it << "," << m[*it].m_name <<"," << m[*it].m_score[1] << ",";//只储存决赛的成绩
	}
	ofs << "\n";//ofs << endl;
	ofs.close();
	cout << "文件储存成功" << endl;
}
//读取记录
void  speechManager::loadRecord()
{
	ifstream ifs("speech.csv", ios::in);

	if (!ifs.is_open())
	{
		this->fileIsEmpty = true;
		cout << "文件为空" << endl;
		ifs.close();//关闭文件
		return;
	}
	//判断是否是被清空
	char ch;
	ifs >> ch;
	if (ifs.eof())
	{
		this->fileIsEmpty = true;
		cout << "文件为空" << endl;
		ifs.close();//关闭文件
		return;
	}
	ifs.putback(ch);
	this->fileIsEmpty = false;

	//截取 并存入这个map<int, vector<string>> record;
	string data;
	int index = 0;
	while (ifs>>data)
	{
		int pos = -1;
		int start = 0;
		
		vector<string> k;
		while (true)
		{
			pos = data.find(",", start);
			if (pos == -1)
			{
				string temp = data.substr(start, data.size() - start);
				k.push_back(temp);
				break;
			}
			
			string temp = data.substr(start, pos);
			k.push_back(temp);
			cout << temp;

			start = pos+1;
		}
		cout << index;
		record.insert(make_pair(1,k));
		index++;
	}
	ifs.close();
}
//查看往届记录

// 清空记录

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
 