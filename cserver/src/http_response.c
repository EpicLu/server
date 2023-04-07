#include "chttp.h"

// 给浏览器做应答
// 参1客户端套接字 参2文件名
void http_response(int cfd, char *file, void *arg)
{
    if (strcmp(file, "/") == 0)
        strcpy(file, "index.html");
    struct myevent_t *ev = (struct myevent_t *)arg;

    struct stat sbuf;
    int ret = stat(file, &sbuf);
    if (ret == -1)
    {
        perror("stat error");
        // 返回404页面
        http_response(cfd, "404.html", ev);
        close(ev->fd);
    }
    // 是普通文件的话
    if (S_ISREG(sbuf.st_mode))
    {
        // 回发HTTP应答
        sprintf(ev->buf, "HTTP/1.1 200 OK\r\n");
        sprintf(ev->buf + strlen(ev->buf), "Content-Type: %s\r\n", http_get_type(file));
        sprintf(ev->buf + strlen(ev->buf), "Content-Length: %ld\r\n", sbuf.st_size);
        sprintf(ev->buf + strlen(ev->buf), "Connection: keep-alive\r\n");
        sprintf(ev->buf + strlen(ev->buf), "\r\n");
        ev->len = strlen(ev->buf);
        event_send_data(cfd, EPOLLIN | EPOLLET, ev);

        // 回发文件数据
        ret = http_send_file(cfd, file);
        if (ret == -1)
            perror("send error");

        // 发送完关闭
        // close(ev->fd);
    }
    // 是目录的话
}