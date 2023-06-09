#include "chttp.h"

// 按行获取HTTP请求
int http_get_line(int cfd, char *buf, int size)
{
    int i = 0;
    char c = '\0';
    int n;

    while ((i < size - 1) && (c != '\n'))
    {
        n = recv(cfd, &c, 1, 0);
        if (n > 0)
        {
            if (c == '\r')
            {
                n = recv(cfd, &c, 1, MSG_PEEK); // MSG_PEEK表拷贝缓冲区的内容 不直接取
                if ((n > 0) && (c == '\n'))
                    recv(cfd, &c, 1, 0);
                else
                    c = '\r';
            }
            buf[i] = c;
            i++;
        }
        else
            c = '\n';
    }
    buf[i] = '\0';

    if (n == -1)
        i = n;

    return i;
}
