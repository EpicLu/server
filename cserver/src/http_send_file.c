#include "chttp.h"

// 给客户端发送请求的文件
void http_send_file(int cfd, void *arg, char *buf)
{
    char *file = (char *)arg;
    char *dot = strrchr(file, '.');
    strncat(file, ".zip", 5);
    int ret, i = 0;
    char sbuf[BUFSIZ];

    int fd = open(file, O_RDONLY);
    if (fd == -1)
    {
        perror("file open error ");
        return;
    }

    while ((ret = read(fd, sbuf, sizeof(sbuf))) != 0)
    {
        printf("read file: %s bufsize:%d\n", file, ret);
    tryagain:
        ret = send(cfd, sbuf, ret, 0);
        printf("send file: %s bufsize:%d\n", file, ret);
        if (ret == -1)
        {
            if (ret == EAGAIN || ret == EINTR) // 阻塞状态不算发送错误
                goto tryagain;
            else
            {
                perror("send error ");
                break;
            }
        }
    }

    close(fd);

    if (ret != -1)
        printf("send file: %s success\n", file);
    else
        printf("send file: %s failed\n", file);

    close(cfd);
}