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
void wall::initwall(int row, int col)
{
    // 首先给屏幕vector开辟空间
    myscreen.resize(col); // 一行
    for_each(myscreen.begin(), myscreen.end(), [=](vector<char> & a) // 一列
             {
                a.resize(row);
             });

    // i是列
    for (int i = 0; i < col; ++i)
    {
        // j 是行
        for (int j = 0; j < row; ++j)
        {
            if (i == 0 || i == col - 1 || j == 0 || j == row - 1)
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
