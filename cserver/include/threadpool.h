#ifndef __THREADPOOL_H__
#define __THREADPOOL_H__

#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <signal.h>
#include <errno.h>

#define DEFAULT_TIME 7
#define MIN_WAIT_TASK_NUM 10
#define DEFAULT_THREAD_VARY 10
#define true 1
#define false 0

typedef struct
{
    void *(*function)(void *);
    void *arg;
} threadpool_task_t;

typedef struct
{
    pthread_mutex_t lock;           // 用于锁住本结构体
    pthread_mutex_t thread_counter; // 记录忙状态线程个数的锁
    pthread_mutexattr_t attr;       // 定义一个锁属性

    pthread_cond_t queue_not_full;  // 当任务队列满时，添加任务的现存阻塞，等待此条件变量
    pthread_cond_t queue_not_empty; // 任务队列不为空时，通知等待任务的线程

    pthread_t *threads;            // 存放线程池中每个线程的pid
    pthread_t adjust_tid;          // 存管理线程tid
    threadpool_task_t *task_queue; // 任务对列

    // 线程池相关
    int min_thr_num;
    int max_thr_num;
    int live_thr_num;
    int busy_thr_num;
    int wait_exit_thr_num;    // 需要销毁的线程个数
    int free_exit_thr_num;    // 因空闲而退出的
    int *free_exit_thr_index; // 存放因空闲退出的线程在threads中的索引

    // 任务队列相关
    int queue_front;
    int queue_back;
    int queue_size;
    int queue_max_size;

    int shutdown; // 线程池使用状态
} threadpool_t;

void *threadpool_thread(void *threadpool);

void *threadpool_adjust(void *threadpool);

int threadpool_add(threadpool_t *pool, void *(*function)(void *arg), void *arg);

int threadpool_destory(threadpool_t *pool);

int threadpool_free(threadpool_t *pool);

threadpool_t *threadpool_create(int min_thr_num, int max_thr_num, int queue_max_size);

// 线程池线程处理数据函数模板
/*void *process(void* arg)
{
    printf("thread 0x%x working on task %d\n", (unsigned int)pthread_self(), *((int*)arg));
    //此处添加任务
    sleep(1);
    printf("task %d is end\n", *((int*)arg));

    return NULL;
}*/

#endif
