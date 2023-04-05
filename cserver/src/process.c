#include "epollheap.h"

// 线程回调函数
void *process(void *arg)
{
    struct myevent_s *ev = (struct myevent_s *)arg;
    printf("thread 0x%x working on task %d\n", (unsigned int)pthread_self(), ev->fd);
    // 此处添加任务
    ev->call_back(ev->fd, ev->events, ev->arg);

    return NULL;
}