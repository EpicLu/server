#include "epollheap.h"

/* 从epoll 监听的 红黑树中删除一个文件描述符*/
void event_del(int efd, struct myevent_t *ev)
{
    struct epoll_event epv = {0, {0}};
    if (ev->status != 1) // 如果fd没有添加到监听树上，就不用删除，直接返回
        return;
    epv.data.ptr = NULL;
    ev->status = 0;
    epoll_ctl(efd, EPOLL_CTL_DEL, ev->fd, &epv);
    return;
}