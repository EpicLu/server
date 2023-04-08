#include "chttp.h"

// 给客户端发送请求的文件
void http_send_file(int cfd, void *arg)
{
    char *file = (char *)arg;
    char buf[BUFSIZ];
    int ret;

    printf("send file: %s\n", file);

    int fd = open(file, O_RDONLY);
    if (fd == -1)
    {
        perror("file open error ");
    }

    while ((ret = read(fd, buf, sizeof(buf))) != 0)
    {
    tryagain:
        ret = send(cfd, buf, ret, 0);
        printf("file: %s bufsize:%d\n", file, ret);
        if (ret == -1)
        {
            if (ret == EAGAIN || ret == EINTR) // 阻塞状态不算发送错误
                goto tryagain;
            else
            {
                perror("send file error ");
                break;
            }
        }
    }

    printf("send file: %s success\n", file);

    // 发送完关闭
    close(fd);
    // close(cfd);
}