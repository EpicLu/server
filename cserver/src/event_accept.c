#include "epollheap.h"
// #include "slave.h"

struct myevent_t g_myevents[MAX_EVENTS + 1];

/*  当有文件描述符就绪, epoll返回, 调用该函数与客户端建立链接 */
void event_accept(int lfd, int events, void *arg)
{
    struct sockaddr_in cin;
    socklen_t len = sizeof(cin);

    int cfd, i;
    if ((cfd = accept(lfd, (struct sockaddr *)&cin, &len)) == -1)
    {
        if (errno != EAGAIN && errno != EINTR)
        {
            printf("%s:accept,%s\n", __func__, strerror(errno));
            return;
        }
    }
    do
    {
        for (i = 0; i < MAX_EVENTS; i++) // 从全局数组g_events中找一个空闲元素，类似于select中找值为-1的元素
        {
            if (g_myevents[i].status == 0)
                break;
        }
        if (i == MAX_EVENTS) // 超出连接数上限
        {
            printf("%s: max connect limit[%d]\n", __func__, MAX_EVENTS);
            break;
        }
        int flag = 0;
        if ((flag = fcntl(cfd, F_SETFL, O_NONBLOCK)) < 0) // 将cfd也设置为非阻塞
        {
            printf("%s: fcntl nonblocking failed, %s\n", __func__, strerror(errno));
            break;
        }
        event_set(&g_myevents[i], cfd, event_recv_data, &g_myevents[i]); // 找到合适的节点之后，将其添加到监听树中，并监听读事件
        event_add(g_efd, EPOLLIN | EPOLLET, &g_myevents[i]);
    } while (0);

    printf("new connect[%s:%d],[time:%ld],pos[%d]\n\n", inet_ntoa(cin.sin_addr), ntohs(cin.sin_port), g_myevents[i].last_active, i);
    return;
}
