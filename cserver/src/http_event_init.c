#include "chttp.h"

/*创建 socket, 初始化lfd */
int http_event_init(int efd, short port, struct myevent_t *myevents)
{
    int ret;
    int opt = 1;
    struct sockaddr_in sin;

    int lfd = socket(AF_INET, SOCK_STREAM, 0);
    if (lfd == -1)
    {
        perror("listensocket error ");
        return -1;
    }
    ret = fcntl(lfd, F_SETFL, O_NONBLOCK); // 将socket设为非阻塞
    if (ret == -1)
    {
        perror("fcntl lfd O_NONBLOCK error ");
        return -1;
    }

    memset(&sin, 0, sizeof(sin)); // bzero(&sin, sizeof(sin))
    sin.sin_family = AF_INET;
    sin.sin_addr.s_addr = INADDR_ANY;
    sin.sin_port = htons(port);

    ret = bind(lfd, (struct sockaddr *)&sin, sizeof(sin));
    if (ret == -1)
    {
        perror("bind error ");
        return -1;
    }

    ret = listen(lfd, MAX_EVENTS);
    if (ret == -1)
    {
        perror("listen error ");
        return -1;
    }

    ret = setsockopt(lfd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)); // 端口复用
    if (ret == -1)
    {
        perror("setsockopt error ");
        return -1;
    }

    /* void event_set(struct myevent_t *ev, int fd, void (*call_back)(int, int, void *), void *arg);  */
    event_set(&myevents[MAX_EVENTS], lfd, http_event_accept, &myevents[MAX_EVENTS]);

    /* void event_add(int efd, int events, struct myevent_t *ev) */
    event_add(efd, EPOLLIN | EPOLLET, &myevents[MAX_EVENTS]); // 将lfd添加到监听树上，监听读事件

    return 0;
}