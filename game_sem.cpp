/*************************************************************************
> File Name: game.cpp
> Author: 
> Mail: 
> Created Time: 2019年06月02日 星期日 17时32分05秒
************************************************************************/

#include <iostream>
#include "wall.h"
#include "snake.h"
#include "food.h"
#include <ctime>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>
using namespace std;
// 业务逻辑：游戏开始到按下第一个有效按键之前，处于静止状态
// 一旦按下有效按键，游戏开始。蛇自动执行上一次的有效按键的操作
// 按下非有效案件一律无效。
// 无法按下与当前按键相对的（180度）的按键


// ---------------使用信号量sem--------------------\\
        // 生产者：getchar, 消费者：判断getchar是否符合规范
// 主界面是不断循环的，不在生产者和消费者之中。

char key = 'q';
char prekey = 'q';

struct arg2
{
    snake * mysnake;
    wall * mw;

};
struct c_arg
{
    char * ktmp;
    snake * mysnake;
};

// 定义信号量

sem_t produce;
sem_t consumer;


// 生产者没生产一个字符
void * producers(void *arg)
{
    char *tmp = (char *)arg;
    while(1)
    {
        sem_wait(&produce);
        *tmp = getchar();
        cout << "getcharar is " << *tmp << endl;
        sem_post(&consumer);

    }}

// 消费者就去判别字符的合理性
void * consumers(void * arg)
{

    char * tmp = ((c_arg*)arg)->ktmp;
    snake * mysnake = ((c_arg*)arg)->mysnake;
    while(1)
    {
        sem_wait(&consumer);
        // 首先，字符得是上下左右之一
        if (*tmp == mysnake->UP || *tmp == mysnake->RIGHT ||*tmp == mysnake->LEFT ||*tmp == mysnake->DOWN)
        {
            cout << "key is " << tmp << endl;
            // 如果输入的前后两个按键是180度的
            if ((*tmp == mysnake->LEFT && prekey == mysnake->RIGHT)||
                (*tmp == mysnake->RIGHT && prekey == mysnake->LEFT)||
                (*tmp == mysnake->UP && prekey == mysnake->DOWN)||
                (*tmp == mysnake->DOWN && prekey == mysnake->UP))
            {
                cout << "输入相反" << endl;
                // 输入无效，仍然启用之前的按键
                *tmp = prekey;
            }
            key = *tmp;
        }
        else // 如果不是输入的上下左右四个按键，就输入无效
        {
            cout << "输入无效" << endl;
            key = prekey;
            // 加一个睡眠，防止加死锁（这个线程太快，总是抢到锁)
        }

        sem_post(&produce);
    }}

// 持续更新画面
void * keeploop(void *arg)
{

    arg2 *myarg2 = (arg2*)arg;
    snake * mysnake = myarg2->mysnake;
    wall * mw = myarg2->mw;
    bool isdead  = false;
    while(!isdead)
    {

        prekey = key;
        cout << "prekey is" << prekey << "key is" << key << endl;
        if (mysnake->move(key) == true)
        {
            system("clear");
            mw->drawall();
            usleep(200000);
        }
        else
        {

            cout << prekey << "," << key << endl;
            isdead = true;
        }
    }

}

int main()
{
    // 设置随机数种子
    srand((unsigned int )(time(NULL)));
    // 初始化定义
    wall *mw = new wall;
    food myfood(*mw);
    snake *mysnake = new snake(*mw, myfood);
    // 设置墙
    mw->initwall();

    // 初始化蛇
    mysnake->initsnake();
    // 初始化食物
    myfood.setfood();

    // 移动测试
    mw->drawall();

    // 设置堆区变量
    arg2 * myarg2 = new arg2;
    myarg2->mw = mw;
    myarg2->mysnake = mysnake;

    char * ktmp = new char;
    *ktmp = 'q';

    c_arg * my_c_arg = new c_arg;
    my_c_arg->ktmp = ktmp;
    my_c_arg->mysnake = mysnake;

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
    // 开启一个新的进程用于接受键盘的输入
    sem_init(&produce, 0, 1);
    sem_init(&consumer, 0, 0);

    pthread_t thread0;
    pthread_t thread1;
    pthread_t thread2;
    pthread_create(&thread0, NULL, producers, ktmp);
pthread_create(&thread1, NULL, consumers, my_c_arg);
pthread_create(&thread2, NULL, keeploop, myarg2);



    // 阻塞等待子线程
    pthread_join(thread2, NULL);
    pthread_join(thread1, NULL);
    pthread_join(thread0, NULL);
    sem_destroy(&produce);
    sem_destroy(&consumer);

    delete my_c_arg;
    delete ktmp;
    delete mysnake;
    delete mw;
    delete myarg2;
    return 0;
}

