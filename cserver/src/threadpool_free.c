#include "threadpool.h"

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