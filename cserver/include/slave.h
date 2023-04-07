/*******************************/
/*-----------------------------*/
/***此头文件存放main函数用到的函数***/
/*******以及全局变量和结构体*******/
/*-----------------------------*/
/*******************************/

// #ifndef __SLAVE_H__
// #define __SLAVE_H__

// #include "epollheap.h"
// #include "threadpool.h"

/* 理想很丰满现实很骨感
// 从线程工作需要用到的数据结构体
struct slave_t
{
    threadpool_t *thp;                         // 线程池结构体地址
    pthread_mutex_t lock;                      // 用来锁住nfd 防止主线程在从线程工作时改掉了nfd
    struct epoll_event events[MAX_EVENTS + 1]; // epoll_wait的传出参数
    int nfd;                                   // epoll_wait返回的值 给从线程用
};
*/

// 全局变量 自定义结构体类型数组. +1-->listen fd
// extern struct myevent_t g_myevents[MAX_EVENTS + 1];

/*******main函数单独用到的函数*******/

// void *slave_thread(void *arg); // 从线程

// void *slave_process(void *arg); // 线程工作函数 在process.c中可修改

// struct slave_t *slave_init(threadpool_t *pool);

// #endif
