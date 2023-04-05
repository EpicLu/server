#include "threadpool.h"
#include "epollheap.h"

void *process(void *arg); // 线程工作函数 在process.c中可修改

int g_efd;
struct myevent_s g_events[MAX_EVENTS + 1];

int main(int argc, char *argv[])
{
    int port = SERV_PORT;

    threadpool_t *thp = threadpool_create(10, 100, 100);
    printf("pool inited\n");

    g_efd = epoll_create(MAX_EVENTS + 1); // 创建红黑树,返回给全局 g_efd
    if (g_efd <= 0)
        printf("create efd in %s err %s\n", __func__, strerror(errno));

    event_init(g_efd, port); // 初始化监听socket

    struct epoll_event events[MAX_EVENTS + 1]; // 定义这个结构体数组，用来接收epoll_wait传出的满足监听事件的fd结构体
    printf("server running:port[%d]\n", port);

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
                ;
            checkpos = 0;
            if (g_events[checkpos].status != 1)
                continue;
            long duration = now - g_events[checkpos].last_active;
            if (duration >= 60)
            {
                close(g_events[checkpos].fd);
                printf("[fd=%d] timeout\n", g_events[checkpos].fd);
                event_del(g_efd, &g_events[checkpos]);
            }
        }
        // 调用eppoll_wait等待接入的客户端事件,epoll_wait传出的是满足监听条件的那些fd的struct epoll_event类型
        int nfd = epoll_wait(g_efd, events, MAX_EVENTS + 1, -1);
        if (nfd < 0)
        {
            printf("epoll_wait error, exit\n");
            exit(-1);
        }
        for (i = 0; i < nfd; i++)
        {
            // evtAdd()函数中，添加到监听树中监听事件的时候将myevents_t结构体类型给了ptr指针
            // 这里epoll_wait返回的时候，同样会返回对应fd的myevents_t类型的指针
            struct myevent_s *ev = (struct myevent_s *)events[i].data.ptr;
            // 如果监听的是读事件，并返回的是读事件
            if ((events[i].events & EPOLLIN) && (ev->events & EPOLLIN))
            {
                if (ev->call_back == event_acceptconn)
                    ev->call_back(ev->fd, events[i].events, ev->arg);
                else
                    threadpool_add(thp, process, (void *)ev);
            }
            // 如果监听的是写事件，并返回的是写事件
            if ((events[i].events & EPOLLOUT) && (ev->events & EPOLLOUT))
            {
                threadpool_add(thp, process, (void *)ev);
            }
        }
    }
    threadpool_destory(thp);

    return 0;
}
