#include "epollheap.h"

/* 向 epoll监听的红黑树 添加一个文件描述符 */
void event_add(int efd, int events, struct myevent_s *ev)
{
    struct epoll_event epv = {0, {0}};
    int op = 0;
    epv.data.ptr = ev;                // ptr指向一个结构体（之前的epoll模型红黑树上挂载的是文件描述符cfd和lfd，现在是ptr指针）
    epv.events = ev->events = events; // EPOLLIN 或 EPOLLOUT
    if (ev->status == 0)              // status 说明文件描述符是否在红黑树上 0不在，1 在
    {
        op = EPOLL_CTL_ADD; // 将其加入红黑树 g_efd, 并将status置1
        ev->status = 1;
    }
    if (epoll_ctl(efd, op, ev->fd, &epv) < 0) // 添加一个节点
        printf("event add failed [fd=%d],events[%d]\n", ev->fd, events);
    else
        printf("event add OK [fd=%d],events[%0X]\n", ev->fd, events);
    return;
}