#include "threadpool.h"

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