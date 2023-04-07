#include "chttp.h"

// 给浏览器做应答
// 参1客户端套接字 参2文件名
void http_request(int fd, const char *file, void *arg)
{
    struct myevent_t *ev = (struct myevent_t *)arg;
    struct stat sbuf;
    int ret = stat(file, &sbuf);
    if (ret == -1)
    {
        perror("stat error");
        // 返回404页面

        close(ev->fd);
    }
    // 是普通文件的话
    if (S_ISREG(sbuf.st_mode))
    {
        char *type;
        // 回发HTTP应答
        sprintf(ev->buf, "HTTP/1.1 200 OK\r\n");
        sprintf(ev->buf + strlen(ev->buf), "Content-Type: %s charset=utf-8\r\n", http_get_type(fd, type));
        sprintf(ev->buf + strlen(ev->buf), "Content-Length: %ld\r\n", sbuf.st_size);
        ev->len = strlen(ev->buf);
        event_set(ev, fd, event_send_data, ev);   // 设置该fd对应的回调函数为senddata
        event_add(g_efd, EPOLLOUT | EPOLLET, ev); // 将fd加入红黑树g_efd中,监听其写事件
        // 回发文件数据 2023年4月7日03:01:00
    }
    // 是目录的话
}