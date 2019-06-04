/*************************************************************************
  > File Name: snake.cpp
  > Author: 
  > Mail: 
  > Created Time: 2019年06月03日 星期一 10时21分46秒
 ************************************************************************/

#include<iostream>
using namespace std;
#include "snake.h"

void snake::initsnake()
{
    // 初始状态下，有蛇头和两节蛇身
    addpoint(5,3);
    addpoint(5,4);
    addpoint(5,5);
}

void snake::addpoint(int x, int y)
{
    // 添加节点的规则是头查法
    point mypoint = {x, y};
    // 如果蛇非空的
    if (!mysnake.empty()) 
    {
        point tmp = mysnake.front();
        mywall.setwall(tmp.x, tmp.y, '=');
    }
    // 否则添加蛇头
    mysnake.push_front(mypoint);
    mywall.setwall(x, y, '@');
}

// 只删除蛇尾部的字符
void snake::delpoint()
{
    // 将尾部删除
    point tmp = mysnake.back();
    mywall.setwall(tmp.x, tmp.y, ' ');
    mysnake.pop_back();
}

bool snake::move(char key)
{
    int x = mysnake.front().x;
    int y = mysnake.front().y;

    switch (key)
    {
        case 'w': --x; break;
        case 's': ++x; break;
        case 'a': --y; break;
        case 'd': ++y; break;
        default:break;
    }

    // 蛇的禁区
    if (mywall.getwall(x, y) == '*' || mywall.getwall(x, y) == '=')
    {
        if (mysnake.back().x == x && mysnake.back().y == y)
        {
            addpoint(x, y);
            delpoint();
            mywall.setwall(x, y, '@');
            return true;
        }
        cout << "game over" << endl;
        return false;
    }
    // 移动成功
    // 吃到食物
    if (mywall.getwall(x, y) == '#')
    {
        addpoint(x, y);
        // 重新设置食物
        myfood.setfood();
    }
    else // 没吃到食物
    { 
        addpoint(x, y);
        delpoint();
    }
    return true;
}

