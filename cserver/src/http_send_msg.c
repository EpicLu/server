#include "chttp.h"

/*发送给客户端数据*/
void http_send_msg(int cfd, int events, void *arg)
{
    struct http_myevent_t *hev = (struct http_myevent_t *)arg;
    int len;

    event_del(g_efd, &(hev->mev)); // 从红黑树g_efd中移除

    len = send(cfd, (hev->mev).buf, (hev->mev).len, 0);

    pthread_mutex_unlock(&(hev->lock)); // 信息发送完后解锁

    if (len > 0)
        printf("send[cfd=%d], buf[%d]\nHTTP RESPOSE\n%s", cfd, len, (hev->mev).buf);
    else
    {
        // close(ev->fd); // 关闭链接
        // 没想好发送数据失败的动作 先保持连接等对方继续请求
        printf("sendmsg[cfd=%d] error %s\n", cfd, strerror(errno));
    }
}