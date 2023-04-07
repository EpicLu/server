/*
#include "slave.h"

// 从线程 处理监听事件
void *slave_thread(void *arg)
{
    struct slave_t *sthr = (struct slave_t *)arg;

    int checkpos = 0;
    int i;
    while (1)
    {
        // 超时设置
        long now = time(NULL);
        for (i = 0; i < 100; i++)
        {
            checkpos++;
            if (checkpos == MAX_EVENTS)
                checkpos = 0;
            if (g_myevents[checkpos].status != 1)
                continue;
            long duration = now - g_myevents[checkpos].last_active;
            if (duration >= 120)
            {
                close(g_myevents[checkpos].fd);
                printf("[fd=%d] timeout\n", g_myevents[checkpos].fd);
                event_del(g_efd, &g_myevents[checkpos]);
            }
        }
        // 监听到事件后分配给线程池就绪的线程处理
        if (sthr->nfd < 0)
        {
            perror("slave_thread epoll_wait error, exit");
            pthread_exit(NULL);
        }
        for (i = 0; i < sthr->nfd; i++)
        {
            // evtAdd()函数中，添加到监听树中监听事件的时候将myevents_t结构体类型给了ptr指针
            // 这里epoll_wait返回的时候，同样会返回对应fd的myevents_t类型的指针
            struct myevent_t *ev = (struct myevent_t *)(sthr->events[i]).data.ptr;

            // 如果监听的是读事件，并返回的是读事件,加回调函数的判断是因为读事件有连接事件和IO事件
            // 此线程是负责处理IO的
            if (((sthr->events[i]).events & EPOLLIN) && (ev->events & EPOLLIN))
            {
                if (ev->call_back == event_accept_conn)
                    ev->call_back(ev->fd, ev->events, ev);
                else
                    threadpool_add(sthr->thp, slave_process, (void *)ev);
            }
            // 如果监听的是写事件，并返回的是写事件
            else if (((sthr->events[i]).events & EPOLLOUT) && (ev->events & EPOLLOUT))
                threadpool_add(sthr->thp, slave_process, (void *)ev);
        }
    }
}
*/