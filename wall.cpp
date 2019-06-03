/*************************************************************************
	> File Name: wall.cpp
	> Author: 
	> Mail: 
	> Created Time: 2019年06月02日 星期日 16时59分25秒
 ************************************************************************/

#include<iostream>
#include "wall.h"
using namespace std;


// 初始化墙壁的大小
void wall::initwall()
{
    // 首先给屏幕vector开辟空间
    myscreen.resize(COL); // 一行
    for_each(myscreen.begin(), myscreen.end(), [=](vector<char> & a) // 一列
             {
                a.resize(ROW);
             });

    // i是列
    for (int i = 0; i < COL; ++i)
    {
        // j 是行
        for (int j = 0; j < ROW; ++j)
        {
            if (i == 0 || i == COL - 1 || j == 0 || j == ROW - 1)
                myscreen[i][j] = '*';
            else
                myscreen[i][j] = ' '; //即使是空的字符，也需要初始化
        }
    }
}


// 绘制出墙壁
void wall::drawall()
{
    for_each(myscreen.begin(), myscreen.end(), [](const vector<char> & v1)
             {
                 for_each(v1.begin(), v1.end(), [](char c){
                        cout << c << " ";
                 });
                 cout << endl;
             });
}


// setwall
void wall::setwall(int x, int y, char c)
{
    myscreen[x][y] = c;
}

// getwakk
char wall::getwall(int x, int y)
{
    return myscreen[x][y];
}

