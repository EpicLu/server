#include "epollheap.h"

/*读取客户端发过来的数据的函数*/
void event_recv_data(int cfd, int events, void *arg)
{
    struct myevent_t *ev = (struct myevent_t *)arg;
    int len;
    char line[1024] = {0};

    len = http_get_line(cfd, line, sizeof(line)); // 读取客户端发过来的数据

    if (len > 0)
    {
        char method[16], path[256], protocol[16];

        sscanf(line, "%[^ ] %[^ ] %[^ ]", method, path, protocol);
        printf("%s %s %s\n", method, path, protocol); // 打印HTTP请求的方法

        // 获得HTTP请求其他信息
        /*
                char buf[BUFSIZ];
                while (http_get_line(cfd, buf, sizeof(buf)) != 1)
                    printf("----%s", buf);
        */
        if (strncmp(method, "GET", 3) == 0)
        {
            if (strcmp(path, "/") == 0)
                http_response(cfd, path, ev);
            else
            {
                char *file = path + 1; // +1是因为getline获得的是/finename的形式 要把/去掉
                http_response(cfd, file, ev);
            }
        }
        else if (strncmp(method, "POST", 4) == 0)
        {
            // post处理事件
        }
        else
        {
            event_set(ev, cfd, event_recv_data, ev); // 将该fd的回调函数改为recvdata
            event_add(g_efd, EPOLLIN | EPOLLET, ev); // 重新添加到红黑树上，设为监听读事件
        }
    }
    else if (len == 0)
    {
        event_set(ev, cfd, event_recv_data, ev); // 将该fd的回调函数改为recvdata
        event_add(g_efd, EPOLLIN | EPOLLET, ev); // 重新添加到红黑树上，设为监听读事件
    }

    else
    {
        close(ev->fd);
        printf("read[cfd=%d] error %s\n", cfd, strerror(errno));
    }
}