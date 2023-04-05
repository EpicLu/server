#include "threadpool.h"

// 工作线程
void *threadpool_thread(void *threadpool)
{
    threadpool_t *pool = (threadpool_t *)threadpool;
    threadpool_task_t task;

    while (1)
    {
        pthread_mutex_lock(&(pool->lock));

        while ((pool->queue_size == 0) && (!pool->shutdown)) // 如果没任务
        {
            printf("thread 0x%x is waiting\n\n", (unsigned int)pthread_self());
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
        printf("==================================\n");
        printf("thread 0x%x start working\n", (unsigned int)pthread_self());
        pthread_mutex_lock(&(pool->thread_counter));
        pool->busy_thr_num++;
        pthread_mutex_unlock(&(pool->thread_counter));
        (*(task.function))(task.arg);

        // 执行完更新busy
        printf("thread 0x%x end working\n", (unsigned int)pthread_self());
        printf("==================================\n\n");
        pthread_mutex_lock(&(pool->thread_counter));
        pool->busy_thr_num--;
        pthread_mutex_unlock(&(pool->thread_counter));
    } // while(1)

    pthread_exit(NULL);
}