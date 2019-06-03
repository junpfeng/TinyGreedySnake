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
#include <fcntl.h>
//#include <thread>
//#include <mutex>

using namespace std;
// 业务逻辑：游戏开始到按下第一个有效按键之前，处于静止状态
// 一旦按下有效按键，游戏开始。蛇自动执行上一次的有效按键的操作
// 按下非有效案件一律无效。
// 无法按下与当前按键相对的（180度）的按键
char key = 'q';

pthread_mutex_t pmt;
void* getkeyborad(void *arg)
{
    while(1)
    {
        pthread_mutex_lock(&pmt);
        key = getchar();
        cout << "按下了：" <<  key << endl;
        pthread_mutex_unlock(&pmt);

        if ( key  == '0')
        break;
    }
  cout << "thread key is " << key << endl;

    return NULL;

};
int main()
{
    // 设置随机数种子
    srand((unsigned int )(time(NULL)));
    // 初始化定义
    wall mw;
    food myfood(mw);
    snake mysnake(mw, myfood);
    // 设置墙
    mw.initwall();

    // B
    // 初始化蛇
    mysnake.initsnake();
    // 初始化食物
    myfood.setfood();

    // 移动测试
    mw.drawall();
    char prekey = 'q';
    //    cin >> key;
    bool isdead = false; // 死亡标志位
    // 开mZ一个新的进程用于接受键盘的输入

    pthread_mutex_init(&pmt, NULL);

    pthread_t thread;


    // 关闭缓冲区，已达到不需要回车自动接受键盘输入
    system("stty -icanon");
    while(1)
    {
        key = getchar();
        if (key == mysnake.LEFT && prekey == 'q')
        {
            cout << "left is wrongg" << endl;
            continue;
        }

        break;
    }
    pthread_create(&thread, NULL, getkeyborad, NULL);
    while(!isdead)
    {
        if (key == mysnake.UP || key == mysnake.RIGHT ||key == mysnake.LEFT ||key == mysnake.DOWN)
        {
            cout << "key is " << key << endl;
            if ((key == mysnake.LEFT && prekey == mysnake.RIGHT)||
                (key == mysnake.RIGHT && prekey == mysnake.LEFT)||
                (key == mysnake.UP && prekey == mysnake.DOWN)||
                (key == mysnake.DOWN && prekey == mysnake.UP))
            {
                pthread_mutex_lock(&pmt);
                key = prekey;
                pthread_mutex_unlock(&pmt);
                cout << "输入相反" << endl;
            }
            prekey = key;
            if (mysnake.move(key) == true)
            {
                mw.drawall();
                sleep(1);
            }
            else
            {
                isdead = true;
            }
        }
        else
        {
            key = prekey;
            cout << "输入无效" << endl;
        }
    }

    // 阻塞等待子线程
    pthread_join(thread, NULL);
    return 0;
}

