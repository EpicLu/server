#include "threadpool.h"

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