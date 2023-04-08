#include "chttp.h"

// 给浏览器做应答
// 参1客户端套接字 参2文件名
void http_response(int cfd, char *file, void *arg)
{
    if (strcmp(file, "/") == 0)
        strcpy(file, "index.html");
    struct http_myevent_t *hev = (struct http_myevent_t *)arg;

    struct stat sbuf;
    int ret = stat(file, &sbuf);
    if (ret == -1)
    {
        perror("stat error");
        // 返回404页面
        http_response(cfd, "404.html", NULL);
        close((hev->mev).fd);
    }
    // 是普通文件的话
    if (S_ISREG(sbuf.st_mode))
    {
        int len;
        // 修改一下文件名传参方式 22时35分
        if (strcmp(file, "404.html") == 0)
            len = http_create_msg((hev->mev).buf, 404, "Not Found", file, sbuf.st_size);
        else
            len = http_create_msg((hev->mev).buf, 200, "OK", file, sbuf.st_size);
        (hev->mev).len = len;
        // 回发HTTP应答
        pthread_mutex_lock(&(hev->lock)); // 锁住回调函数
        event_set(&(hev->mev), cfd, http_send_msg, hev);
        event_add(g_efd, EPOLLOUT | EPOLLET, &(hev->mev));

        // 回发文件数据
        pthread_mutex_lock(&(hev->lock));   // 等上面的回调函数发送完报文完解锁
        pthread_mutex_unlock(&(hev->lock)); // 拿到锁立即解锁 因为报文已发送完 不会有任何事件会占用写缓冲
        event_set(&(hev->mev), cfd, http_send_file, file);
        event_add(g_efd, EPOLLOUT | EPOLLET, &(hev->mev));
    }
    // 是目录的话
}