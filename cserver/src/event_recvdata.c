#include "epollheap.h"

/*读取客户端发过来的数据的函数*/
void event_recvdata(int fd, int events, void *arg)
{
    struct myevent_s *ev = (struct myevent_s *)arg;
    int len;

    len = recv(fd, ev->buf, sizeof(ev->buf), 0); // 读取客户端发过来的数据

    event_del(g_efd, ev); // 将该节点从红黑树上摘除

    if (len > 0)
    {
        ev->len = len;
        ev->buf[len] = '\0'; // 手动添加字符串结束标记
        printf("recv[%d]:%s", fd, ev->buf);

        event_set(ev, fd, event_senddata, ev);    // 设置该fd对应的回调函数为senddata
        event_add(g_efd, EPOLLOUT | EPOLLET, ev); // 将fd加入红黑树g_efd中,监听其写事件
    }
    else if (len == 0)
    {
        close(ev->fd);
        /* ev-g_events 地址相减得到偏移元素位置 */
        printf("[fd=%d] pos[%ld], closed\n", fd, ev - g_events);
    }
    else
    {
        close(ev->fd);
        printf("recv[fd=%d] error[%d]:%s\n", fd, errno, strerror(errno));
    }
    return;
}