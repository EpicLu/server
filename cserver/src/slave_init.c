/*
#include "slave.h"

// 初始化slave_t 结构体
struct slave_t *slave_init(threadpool_t *pool)
{
    struct slave_t *sthp = malloc(sizeof(struct slave_t));

    sthp->thp = pool;

    if (pthread_mutex_init(&(sthp->lock), NULL) != 0)
    {
        perror("lock init error ");
        return NULL;
    }

    memset(sthp->events, 0, sizeof(sthp->events));

    sthp->nfd = 0;

    return sthp;
}
*/