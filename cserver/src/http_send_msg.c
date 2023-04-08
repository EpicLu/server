#include "chttp.h"

/*发送给客户端数据*/
void http_send_msg(int cfd, int events, void *arg)
{
    struct myevent_t *ev = (struct myevent_t *)arg;
    int len;

    event_del(g_efd, ev); // 从红黑树g_efd中移除

    len = send(cfd, ev->buf, ev->len, 0);

    if (len > 0)
    {
        printf("send[cfd=%d], buf[%d]\n\nHTTP RESPOSE\n%s", cfd, len, ev->buf);
        event_set(ev, cfd, http_recv_msg, ev);   // 将该fd的回调函数改为recvdata
        event_add(g_efd, EPOLLIN | EPOLLET, ev); // 重新添加到红黑树上，设为监听读事件
    }
    else
    {
        // close(ev->fd); // 关闭链接
        // 没想好发送数据失败的动作 先保持连接等对方继续请求
        printf("send[cfd=%d] error %s\n", cfd, strerror(errno));
    }
}