#include "epollheap.h"

/*创建 socket, 初始化lfd */
void event_init(int efd, short port)
{
    int opt = 1;
    struct sockaddr_in sin;

    int lfd = socket(AF_INET, SOCK_STREAM, 0);
    fcntl(lfd, F_SETFL, O_NONBLOCK); // 将socket设为非阻塞

    memset(&sin, 0, sizeof(sin)); // bzero(&sin, sizeof(sin))
    sin.sin_family = AF_INET;
    sin.sin_addr.s_addr = INADDR_ANY;
    sin.sin_port = htons(port);

    bind(lfd, (struct sockaddr *)&sin, sizeof(sin));

    listen(lfd, 20);

    setsockopt(lfd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)); // 端口复用

    /* void event_set(struct myevent_s *ev, int fd, void (*call_back)(int, int, void *), void *arg);  */
    event_set(&g_events[MAX_EVENTS], lfd, event_acceptconn, &g_events[MAX_EVENTS]);

    /* void event_add(int efd, int events, struct myevent_s *ev) */
    event_add(efd, EPOLLIN | EPOLLET, &g_events[MAX_EVENTS]); // 将lfd添加到监听树上，监听读事件

    return;
}