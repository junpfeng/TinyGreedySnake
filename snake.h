/*************************************************************************
> File Name: snake.h
> Author: 
> Mail: 
> Created Time: 2019年06月03日 星期一 10时21分56秒
************************************************************************/

#ifndef _SNAKE_H
#define _SNAKE_H
#include <deque>
#include "wall.h"
#include "food.h"

class snake
{
    private:
    wall &mywall;
    food & myfood;
    struct point
    {
        // 数据域
        int x; // 
        int y;
    };
    // deque存放蛇身
    deque<point> mysnake;

    public:
    // 构造
    snake(wall & mywall, food & myfood):mywall(mywall), myfood(myfood)
    {
    }
    
    // 枚举蛇的运动
    enum{
        UP = 'w',
        DOWN = 's',
        LEFT = 'a',
        RIGHT = 'd'
    };

    // 初始化
    void initsnake();
    // 用于删除deque的尾部
    void delpoint();
    // 添加蛇身
    void addpoint(int x, int y);
    // 移动蛇身
    bool move(char key);
};

#endif
