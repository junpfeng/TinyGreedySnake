/*************************************************************************
> File Name: game.cpp
> Author: 
> Mail: 
> Created Time: 2019年06月02日 星期日 17时32分05秒
************************************************************************/

#include<iostream>
#include "wall.h"
#include "snake.h"
#include "food.h"
#include <ctime>
#include <unistd.h>
using namespace std;
// 业务逻辑：游戏开始到按下第一个有效按键之前，处于静止状态
// 一旦按下有效按键，游戏开始。蛇自动执行上一次的有效按键的操作
// 按下非有效案件一律无效。
// 无法按下与当前按键相对的（180度）的按键
char key = 'q';
char prekey = 'q';

pthread_rwlock_t rwlock;

void* getkeyborad(void *ptr)
{
    snake * mysnake = (snake*)ptr;
    char tmp = 'q';
    while(1)
    {
        pthread_rwlock_wrlock(&rwlock);
        tmp = getchar();
        cout << "按下了：" <<  tmp << endl;
        pthread_rwlock_rdlock(&rwlock);
        if (tmp == mysnake->UP || tmp == mysnake->RIGHT ||tmp == mysnake->LEFT ||tmp == mysnake->DOWN)
        {
            cout << "key is " << tmp << endl;
            // 如果输入的前后两个按键是180度的
            if ((tmp == mysnake->LEFT && prekey == mysnake->RIGHT)||
                (tmp == mysnake->RIGHT && prekey == mysnake->LEFT)||
                (tmp == mysnake->UP && prekey == mysnake->DOWN)||
                (tmp == mysnake->DOWN && prekey == mysnake->UP))
            {
                cout << "输入相反" << endl;
                // 输入无效，仍然启用之前的按键
                pthread_rwlock_rdlock(&rwlock);
                tmp = prekey;
                pthread_rwlock_rdlock(&rwlock);
            }
            key = tmp;
        }
        else // 如果不是输入的上下左右四个按键，就输入无效
        {
            cout << "输入无效" << endl;
            // 加一个睡眠，防止加死锁（这个线程太快，总是抢到锁)
        }
        pthread_rwlock_rdlock(&rwlock);
        cout << "thread key is " << key << endl;
        pthread_rwlock_rdlock(&rwlock);
    }
    return NULL;
}

int main()
{
    // 设置随机数种子
    srand((unsigned int )(time(NULL)));
    // 初始化定义
    wall mw;
    food myfood(mw);
    snake *mysnake = new snake(mw, myfood);
    // 设置墙
    mw.initwall();

    // 初始化蛇
    mysnake->initsnake();
    // 初始化食物
    myfood.setfood();

    // 移动测试
    mw.drawall();
    //    cin >> key;
    bool isdead = false; // 死亡标志位

    // 关闭缓冲区，已达到不需要回车自动接受键盘输入---要改
    system("stty -icanon");
    while(1)
    {
        key = getchar();
        if (key == mysnake->LEFT && prekey == 'q')
        {
            cout << "left is wrongg" << endl;
            continue;
        }

        break;
    }
    // 住线程进行循环
    // 开启一个新的进程用于接受键盘的输入
    pthread_rwlock_init(&rwlock, NULL);
    pthread_t thread;
    pthread_create(&thread, NULL, getkeyborad, NULL);
    while(!isdead)
    {

        prekey = key;
        cout << "prekey is" << prekey << "key is" << key << endl;
        if (mysnake->move(key) == true)
        {
            system("clear");
            mw.drawall();
            usleep(200000);
        }
        else
        {

            cout << prekey << "," << key << endl;
            isdead = true;
        }
    }

    // 阻塞等待子线程
    pthread_join(thread, NULL);
    delete mysnake;
    pthread_rwlock_destroy(&rwlock);
    return 0;
}

