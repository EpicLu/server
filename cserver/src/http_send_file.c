#include "chttp.h"

// 给客户端发送请求的文件
int http_send_file(int cfd, const char *file)
{
    char buf[BUFSIZ];
    int ret;

    int fd = open(file, O_RDONLY);
    if (fd == -1)
    {
        perror("file open error ");
        return -1;
    }

    while ((ret = read(fd, buf, sizeof(buf))) != 0)
    {
        ret = send(cfd, buf, ret, 0);
        printf("bufsize: %d\n", ret);
        if (ret == -1)
        {
            if (ret == EAGAIN || ret == EINTR)
                continue;
            else
            {
                perror("send error ");
                return -1;
            }
        }
    }

    close(fd);
    return 0;
}