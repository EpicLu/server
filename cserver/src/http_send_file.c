#include "chttp.h"

// 给客户端发送请求的文件
void http_send_file(int cfd, int events, void *arg)
{
    const char *file = (char *)arg;
    char buf[BUFSIZ];
    int ret;

    int fd = open(file, O_RDONLY);
    if (fd == -1)
    {
        perror("file open error ");
    }

    while ((ret = read(fd, buf, sizeof(buf))) != 0)
    {
        ret = send(cfd, buf, ret, 0);
        if (ret == -1)
        {
            if (ret == EAGAIN || ret == EINTR) // 阻塞状态不算发送错误
                continue;
            else
            {
                perror("send error ");
            }
        }
    }

    close(fd);
}