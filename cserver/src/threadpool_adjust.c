#include "threadpool.h"

// 管理者线程
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