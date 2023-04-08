#include "chttp.h"

/*读取浏览器发过来的数据的函数*/
void http_recv_msg(int cfd, int events, void *arg)
{
    struct http_myevent_t *hev = (struct http_myevent_t *)arg;
    int len;
    char line[1024] = {0};
    char buf[BUFSIZ] = {0};

    event_del(g_efd, &(hev->mev)); // 从红黑树g_efd中移除

    len = http_get_line(cfd, line, sizeof(line)); // 读取浏览器发过来的数据
    while (http_get_line(cfd, buf, sizeof(buf)) != 1)
        ; // 把缓冲区剩余数据读完 读到\r\n

    if (len > 0)
    {
        char method[16], path[256], protocol[16];

        sscanf(line, "%[^ ] %[^ ] %[^ ]", method, path, protocol); // 获取HTTP请求的方法
        printf("%s %s %s\n", method, path, protocol);              // 打印HTTP请求的方法

        // 获得HTTP请求其他信息
        /*
                char buf[BUFSIZ];
                while (http_get_line(cfd, buf, sizeof(buf)) != 1)
                    printf("----%s", buf);
        */

        if (strncmp(method, "GET", 3) == 0) // 如果没请求文件 默认展示首页
        {
            if (strcmp(path, "/") == 0)
                http_response(cfd, path, hev);
            else
            {
                char *file = path + 1; // +1是因为getline获得的是/finename的形式 要把/去掉
                http_response(cfd, file, hev);
            }
        }
        else if (strncmp(method, "POST", 4) == 0)
        {
            // post处理事件
        }
        else
        {
        }
    }
    else if (len == 0)
    {
    }

    else
    {
        close((hev->mev).fd);
        printf("read[cfd=%d] error %s\n", cfd, strerror(errno));
    }
}