#include "threadpool.h"

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

        if (pthread_mutexattr_settype(&(pool->attr), PTHREAD_MUTEX_ADAPTIVE_NP) != 0)

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