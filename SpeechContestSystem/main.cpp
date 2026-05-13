#define _CRT_SECURE_NO_WARNINGS 1

#include <iostream>
#include <ctime>
#include "speechManager.h"
using namespace std;
int main()
{
    //随机种子
    srand((unsigned int)time(NULL));
    speechManager sw;
    int choice = 0;
    while (true)
    {
        sw.showMenu();
        cout << "输入你的选择:" << endl;
        cin >> choice;
        switch (choice)
        {
        case 0:
            //退出比赛程序
            sw.exitSystem();
            break;
        case 1:
            //开始比赛
            sw.startSpeech();
            break;
        case 2:
            //查看记录
            break;
        case 3:
            //清空记录
            break;
        default:
            //退出系统
            system("cls");
            break;
        }

    }
}


 
 

 






