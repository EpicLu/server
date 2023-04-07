#include "epollheap.h"

/*发送给客户端数据*/
void event_send_data(int fd, int events, void *arg)
{
    struct myevent_t *ev = (struct myevent_t *)arg;
    int len;

    event_del(g_efd, ev); // 从红黑树g_efd中移除

    len = send(fd, ev->buf, ev->len, 0);

    if (len > 0)
    {
        printf("send[fd=%d], buf[%d]\n\nHTTP RESPOSE\N%s", fd, len, ev->buf);
        event_set(ev, fd, event_recv_data, ev);  // 将该fd的回调函数改为recvdata
        event_add(g_efd, EPOLLIN | EPOLLET, ev); // 重新添加到红黑树上，设为监听读事件
    }
    else
    {
        // close(ev->fd); // 关闭链接
        // 没想好发送数据失败的动作 先保持连接等对方继续请求
        printf("send[fd=%d] error %s\n", fd, strerror(errno));
    }
}