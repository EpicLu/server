#include "epollheap.h"

/*发送给客户端数据*/
void event_senddata(int fd, int events, void *arg)
{
    struct myevent_s *ev = (struct myevent_s *)arg;
    int len, i;

    for (i = 0; i < ev->len; i++)
        ev->buf[i] = toupper(ev->buf[i]);

    len = send(fd, ev->buf, ev->len, 0); // 直接将数据回射给客户端

    event_del(g_efd, ev); // 从红黑树g_efd中移除

    if (len > 0)
    {
        printf("send[fd=%d], [%d]%s", fd, len, ev->buf);
        event_set(ev, fd, event_recvdata, ev);   // 将该fd的回调函数改为recvdata
        event_add(g_efd, EPOLLIN | EPOLLET, ev); // 重新添加到红黑树上，设为监听读事件
    }
    else
    {
        close(ev->fd); // 关闭链接
        printf("send[fd=%d] error %s\n", fd, strerror(errno));
    }
    return;
}