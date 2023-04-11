#include "threadpool.h"
#include "chttp.h"

void *process(void *arg); // 线程调用函数
// 全局变量 定义在epollheap.h中 epoll_create的返回值
struct http_myevent_t g_hev[MAX_EVENTS + 1];
int g_efd;

// 主线程负责监听事件
int main(int argc, char *argv[])
{
    /*
    char buf[512];
    // 使用getcwd获取启动目录
    if (NULL == getcwd(buf, sizeof(buf)))
    {
        fprintf(stderr, "getcwd error: %s", strerror(errno));
        exit(1);
    }
    printf("current work path: %s\n", buf);
    */
    // 检查运行程序传入的参数
    if (argc < 3)
        printf("./server port path\n");

    int port = atoi(argv[1]);

    int ret = chdir(argv[2]);
    if (ret == -1)
    {
        printf("chdir error!");
        exit(-1);
    }

    // 创建线程池
    threadpool_t *thp = threadpool_create(32, 128, 128);

    g_efd = epoll_create(MAX_EVENTS + 1); // 创建红黑树,返回给全局 g_efd
    if (g_efd <= 0)
        printf("create efd in %s err %s\n", __func__, strerror(errno));

    ret = http_event_init(g_efd, port, g_hev); // 初始化监听socket
    if (ret == -1)
    {
        printf("event_init error!\n");
        exit(-1);
    }
    printf("server running:port[%d]\n", port);

    // 初始化从从线程工作用到的结构体 具体定义在slave.h中
    // struct slave_t *sthr = slave_init(thp);
    // 创建从线程来负责处理事件

    // pthread_t slave_tid;
    // ret = pthread_create(&slave_tid, NULL, slave_thread, (void *)sthr);
    struct epoll_event events[MAX_EVENTS + 1];

    int i;
    int checkpos = 0;
    while (1)
    {
        
        // 超时设置
        long now = time(NULL);
        for (i = 0; i < 100; i++)
        {
            checkpos++;
            if (checkpos == MAX_EVENTS)
                checkpos = 0;
            if (g_myevents[checkpos].status != 1)
                continue;
            long duration = now - g_myevents[checkpos].last_active;
            if (duration >= 120)
            {
                close(g_myevents[checkpos].fd);
                printf("[fd=%d] timeout\n", g_myevents[checkpos].fd);
                event_del(g_efd, &g_myevents[checkpos]);
            }
        }
        
        // 调用eppoll_wait等待接入的客户端事件,epoll_wait传出的是满足监听条件的那些fd的struct epoll_event类型
        int nfd = epoll_wait(g_efd, events, MAX_EVENTS + 1, 0);

        if (nfd == -1 && errno != EAGAIN && errno != EINTR)
        {
            perror("main epoll_wait error, exit ");
            exit(-1);
        }
        for (i = 0; i < nfd; i++)
        {
            // evtAdd()函数中，添加到监听树中监听事件的时候将myevents_t结构体类型给了ptr指针
            // 这里epoll_wait返回的时候，同样会返回对应fd的myevents_t类型的指针
            struct myevent_t *ev = (struct myevent_t *)events[i].data.ptr;

            // 如果监听的是读事件
            if ((events[i].events & EPOLLIN) && (ev->events & EPOLLIN))
                threadpool_add(thp, process, (void *)ev);
            // 如果监听的是写事件，最后一个判断是因为epoll监听到后会立即触发一次写事件
            else if ((events[i].events & EPOLLOUT) && (ev->events & EPOLLOUT) && ev->call_back != http_recv_msg)
            {
                // event_del(g_efd, ev); // 从红黑树g_efd中移除
                // event_set(ev, ev->fd, http_recv_msg, ev); // 将该fd的回调函数改为recvmsg
                // event_add(g_efd, EPOLLIN | EPOLLET, ev);    // 重新添加到红黑树上，设为监听读事件
                threadpool_add(thp, process, (void *)ev); // 如果监听的是写事件，并返回的是写事件
            }
        }
    }
    // 回收从线程 防止僵尸线程
    // pthread_join(slave_tid, NULL);

    // free(sthr);

    threadpool_destory(thp);

    return 0;
}
