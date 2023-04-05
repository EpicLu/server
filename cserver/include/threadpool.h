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

void *threadpool_thread(void *threadpool)
{
    threadpool_t *pool = (threadpool_t *)threadpool;
    threadpool_task_t task;

    while (1)
    {
        pthread_mutex_lock(&(pool->lock));

        while ((pool->queue_size == 0) && (!pool->shutdown)) // 如果没任务
        {
            printf("thread 0x%x is waiting\n", (unsigned int)pthread_self());
            pthread_cond_wait(&(pool->queue_not_empty), &(pool->lock)); // 阻塞等待signal
            while (pool->queue_size == 0)
            { // 此处的while用来处理虚假唤醒，如果用if，可能存在没有资源可用的情况。
                pthread_cond_wait(&pool->queue_not_empty, &(pool->lock));
            }
            // 清除等待退出的线程
            if (pool->wait_exit_thr_num > 0)
            {
                pool->wait_exit_thr_num--;

                // 如果线程池里线程个数大于最小值 结束当前线程
                if (pool->live_thr_num > pool->min_thr_num)
                {
                    int i;
                    printf("thread 0x%x is exiting\n", (unsigned int)pthread_self());
                    for (i = 0; i < pool->live_thr_num; i++)
                        if (pool->threads[i] == pthread_self())
                            pool->free_exit_thr_index[i] = i; // 更新free_exit
                    pool->free_exit_thr_num++;
                    pool->live_thr_num--;
                    pthread_mutex_unlock(&(pool->lock));

                    pthread_exit((void *)pthread_self());
                }
            }
        } // while(没任务)

        if (pool->shutdown)
        {
            pthread_mutex_unlock(&(pool->lock));
            printf("thread 0x%x is exiting\n", (unsigned int)pthread_self());

            pthread_exit(NULL);
        }
        // 从队列任务中获取任务
        task.function = pool->task_queue[pool->queue_front].function;
        task.arg = pool->task_queue[pool->queue_front].arg;
        // 模拟获取到的任务出队
        pool->queue_front = (pool->queue_front + 1) % pool->queue_max_size;
        pool->queue_size--;

        // 通知可以有新的任务添加进来
        pthread_cond_broadcast(&(pool->queue_not_full));

        pthread_mutex_unlock(&(pool->lock));

        // 执行任务
        printf("thread 0x%x start working\n", (unsigned int)pthread_self());
        pthread_mutex_lock(&(pool->thread_counter));
        pool->busy_thr_num++;
        pthread_mutex_unlock(&(pool->thread_counter));
        (*(task.function))(task.arg);

        // 执行完更新busy
        printf("thread 0x%x end working\n", (unsigned int)pthread_self());
        pthread_mutex_lock(&(pool->thread_counter));
        pool->busy_thr_num--;
        pthread_mutex_unlock(&(pool->thread_counter));
    } // while(1)

    pthread_exit(NULL);
}

void *threadpool_adjust(void *threadpool)
{
    int i;
    threadpool_t *pool = (threadpool_t *)threadpool;

    while (!pool->shutdown)
    {
        sleep(DEFAULT_TIME);

        pthread_mutex_lock(&(pool->lock));
        int queue_size = pool->queue_size;
        int live_thr_num = pool->live_thr_num;
        pthread_mutex_unlock(&(pool->lock));

        pthread_mutex_lock(&(pool->thread_counter));
        int busy_thr_num = pool->busy_thr_num;
        pthread_mutex_unlock(&(pool->thread_counter));

        // 创建线程
        if (queue_size >= MIN_WAIT_TASK_NUM && live_thr_num < pool->max_thr_num)
        {
            pthread_mutex_lock(&(pool->lock));
            int add = 0;

            for (i = 0; i < pool->max_thr_num && add < DEFAULT_THREAD_VARY && pool->live_thr_num < pool->max_thr_num; i++)
            {
                if (pool->threads[i] == 0)
                {
                    pthread_create(&(pool->threads[i]), NULL, threadpool_thread, (void *)pool);
                    add++;
                    pool->live_thr_num++;
                }
            }

            pthread_mutex_unlock(&(pool->lock));
        }

        // 销毁空闲进程
        if ((busy_thr_num * 2) < live_thr_num && live_thr_num > pool->min_thr_num)
        {
            pthread_mutex_lock(&(pool->lock));
            pool->wait_exit_thr_num = DEFAULT_THREAD_VARY;
            pthread_mutex_unlock(&(pool->lock));

            for (i = 0; i < DEFAULT_THREAD_VARY; i++)
                pthread_cond_signal(&(pool->queue_not_empty));
        }

        // 回收上述函数销毁的进程
        if (pool->free_exit_thr_num > 0)
        {
            int index;
            pthread_mutex_lock(&(pool->lock));
            for (i = 0; i < pool->free_exit_thr_num; i++)
            {
                index = pool->free_exit_thr_index[i];
                pthread_join(pool->threads[index], NULL);
                pool->threads[index] = 0;
                pool->free_exit_thr_index[i] = 0;
            }
            pthread_mutex_unlock(&(pool->lock));
        }
    }

    return NULL;
}

int threadpool_add(threadpool_t *pool, void *(*function)(void *arg), void *arg)
{
    pthread_mutex_lock(&(pool->lock));

    // 当任务队列满了 阻塞等待queue_not_full条件变量
    while ((pool->queue_size == pool->queue_max_size) && (!pool->shutdown))
        pthread_cond_wait(&(pool->queue_not_full), &(pool->lock));

    // 当线程池关闭了
    if (pool->shutdown)
    {
        pthread_cond_broadcast(&(pool->queue_not_empty));
        pthread_mutex_unlock(&(pool->lock));
        return 0;
    }

    // 清空工作线程调用的回调函数
    if (pool->task_queue[pool->queue_back].arg != NULL)
        pool->task_queue[pool->queue_back].arg = NULL;

    // 添加任务到任务队列里
    pool->task_queue[pool->queue_back].function = function;
    pool->task_queue[pool->queue_back].arg = arg;
    pool->queue_back = (pool->queue_back + 1) % pool->queue_max_size;
    pool->queue_size++;

    // 唤醒线程池中等待任务的线程
    pthread_cond_signal(&(pool->queue_not_empty));
    pthread_mutex_unlock(&(pool->lock));

    return 0;
}

int threadpool_destory(threadpool_t *pool)
{
    int i, n = pool->live_thr_num;
    if (pool == NULL)
        return -1;

    pool->shutdown = true;

    // 先销毁管理者线程
    pthread_join(pool->adjust_tid, NULL);

    for (i = 0; i < n; i++)
        pthread_cond_broadcast(&(pool->queue_not_empty));

    for (i = 0; i < n; i++)
    {
        if (pool->threads[i] != 0)
            pthread_join(pool->threads[i], NULL);
        else
            n++; // 跳过了tid为0的线程 要多迭代一次
    }

    return 0;
}

int threadpool_free(threadpool_t *pool)
{
    if (pool == NULL)
        return -1;

    if (pool->task_queue)
        free(pool->task_queue);

    if (pool->free_exit_thr_index)
        free(pool->free_exit_thr_index);

    if (pool->threads)
    {
        free(pool->threads);
        pthread_mutex_lock(&(pool->lock));
        pthread_mutex_destroy(&(pool->lock));
        pthread_mutex_lock(&(pool->thread_counter));
        pthread_mutex_destroy(&(pool->thread_counter));
        pthread_mutexattr_destroy(&(pool->attr));
        pthread_cond_destroy(&(pool->queue_not_full));
        pthread_cond_destroy(&(pool->queue_not_empty));
    }

    free(pool);
    pool = NULL;

    return 0;
}

threadpool_t *threadpool_create(int min_thr_num, int max_thr_num, int queue_max_size)
{
    int i;
    threadpool_t *pool = NULL;

    do
    {
        if ((pool = (threadpool_t *)malloc(sizeof(threadpool_t))) == NULL)
        {
            printf("malloc threadpoll failed\n");
            break;
        }

        pool->min_thr_num = min_thr_num;
        pool->max_thr_num = max_thr_num;
        pool->busy_thr_num = 0;
        pool->live_thr_num = min_thr_num;
        pool->wait_exit_thr_num = 0;
        pool->free_exit_thr_num = 0;
        pool->queue_size = 0;
        pool->queue_max_size = queue_max_size;
        pool->queue_front = 0;
        pool->queue_back = 0;
        pool->shutdown = false;

        pool->threads = (pthread_t *)malloc(sizeof(pthread_t) * max_thr_num);
        if (pool->threads == NULL)
        {
            printf("malloc threads failed\n");
            break;
        }
        memset(pool->threads, 0, sizeof(pthread_t) * max_thr_num);

        pool->free_exit_thr_index = (int *)malloc(sizeof(int) * DEFAULT_THREAD_VARY);
        if (pool->free_exit_thr_index == NULL)
        {
            printf("malloc index failed\n");
            break;
        }
        memset(pool->free_exit_thr_index, 0, sizeof(int) * DEFAULT_THREAD_VARY);

        pool->task_queue = (threadpool_task_t *)malloc(sizeof(threadpool_task_t) * queue_max_size);
        if (pool->task_queue == NULL)
        {
            printf("malloc taskqueue failed\n");
            break;
        }

        if (pthread_mutexattr_init(&(pool->attr)) != 0)

        {
            printf("init locktype init failed\n");
            break;
        }

        if (pthread_mutexattr_settype(&(pool->attr), PTHREAD_MUTEX_ERRORCHECK) != 0)

        {
            printf("init locktypeset failed\n");
            break;
        }

        if (pthread_mutex_init(&(pool->lock), &(pool->attr)) != 0 || pthread_mutex_init(&(pool->thread_counter), &(pool->attr)) != 0 || pthread_cond_init(&(pool->queue_not_full), NULL) != 0 || pthread_cond_init(&(pool->queue_not_empty), NULL) != 0)
        {
            printf("init lock or cond failed\n");
            break;
        }

        for (i = 0; i < min_thr_num; i++)
        {
            pthread_create(&(pool->threads[i]), NULL, threadpool_thread, (void *)pool);
            printf("start thread 0x%x...\n", (unsigned int)pool->threads[i]);
        }
        pthread_create(&(pool->adjust_tid), NULL, threadpool_adjust, (void *)pool);

        return pool;

    } while (0);

    threadpool_free(pool);

    return NULL;
}

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
