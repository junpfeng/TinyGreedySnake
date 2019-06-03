/*************************************************************************
  > File Name: food.cpp
  > Author: 
  > Mail: 
  > Created Time: 2019年06月03日 星期一 10时05分55秒
 ************************************************************************/

#include<iostream>
using namespace std;
#include "wall.h"
#include "food.h"
// 浅层拷贝可以实现一种类似单例的效果，
// 所以说，浅层拷贝是非常有用的


void food::setfood()
{
    while(1)
    {
        foodx = rand()%(wall::ROW - 2) + 1;
        foody = rand()%(wall::COL - 2) + 1;

        //  只有空白的区域才能放食物
        if (mywall.getwall(foodx, foody) == ' ')
        {
            mywall.setwall(foodx, foody, '#');
            return;
        }
    }   

}

