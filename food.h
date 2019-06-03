/*************************************************************************
	> File Name: food.h
	> Author: 
	> Mail: 
	> Created Time: 2019年06月03日 星期一 09时46分17秒
 ************************************************************************/

#ifndef _FOOD_H
#define _FOOD_H
#include "wall.h"

class food
{
    private:
        int foodx;
        int foody;
        wall & mywall;

    public:
        food(wall & mywall):mywall(mywall){}
        void setfood();
};


#endif
