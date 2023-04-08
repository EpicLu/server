#include "epollheap.h"

/*读取客户端发过来的数据的函数*/
void event_recv_data(int cfd, int events, void *arg)
{
    struct myevent_t *ev = (struct myevent_t *)arg;
    int len;

    event_del(g_efd, ev); // 从红黑树g_efd中移除

    len = recv(cfd, ev->buf, sizeof(ev->buf), 0); // 读取客户端发过来的数据

    if (len > 0)
    {
        printf("recv[cfd=%d], buf[%d]%s\n", cfd, len, ev->buf);
        event_set(ev, cfd, event_send_data, ev);  // 将该fd的回调函数改为recvdata
        event_add(g_efd, EPOLLOUT | EPOLLET, ev); // 重新添加到红黑树上，设为监听读事件
    }
    else if (len == 0)
    {
        close(ev->fd);
        printf("cilent[cfd=%d] closed\n", cfd);
    }
    else
    {
        close(ev->fd);
        printf("read[cfd=%d] error %s\n", cfd, strerror(errno));
    }
}