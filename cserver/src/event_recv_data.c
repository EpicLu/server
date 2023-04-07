#include "epollheap.h"

/*读取客户端发过来的数据的函数*/
void event_recv_data(int fd, int events, void *arg)
{
    struct myevent_t *ev = (struct myevent_t *)arg;
    int len;
    char line[1024] = {0};

    len = http_get_line(fd, line, sizeof(line)); // 读取客户端发过来的数据

    event_del(g_efd, ev); // 将该节点从红黑树上摘除

    if (len > 0)
    {
        char method[16], path[256], protocol[16];

        sscanf(line, "%[^ ] %[^ ] %[^ ]", method, path, protocol);
        // printf("%s %s %s\n", method, path, protocol); //打印HTTP请求的方法

        // 获得HTTP请求其他信息
        /*
        char buf[BUFLEN];
        while (http_get_line(fd, buf, sizeof(buf)) != 1)
            printf("----%s", buf);
        */

        if (strncmp(method, "GET", 3) == 0)
        {
            char *file = path + 1; // +1是因为getline获得的是/finename的形式 要把/去掉
            http_request(fd, file, ev);
        }
        else if (strncmp(method, "POST", 4) == 0)
        {
            // post处理事件
        }
    }
    else if (len == 0) // 客户端关闭
        close(ev->fd);
    else
    {
        close(ev->fd);
        printf("read[fd=%d] error %s\n", fd, strerror(errno));
    }
}