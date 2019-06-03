/*************************************************************************
	> File Name: wall.h
	> Author: 
	> Mail: 
	> Created Time: 2019年06月02日 星期日 16时55分59秒
 ************************************************************************/

#ifndef _WALL_H
#define _WALL_H
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;


class wall
{
    public:
    enum{
        ROW = 20,
        COL = 20
    };
    private:
    vector<vector<char>> myscreen;
    public:
    void initwall(); 
    void drawall();
    void setwall(int x, int y, char c);
    char getwall(int x, int y);
};


#endif
