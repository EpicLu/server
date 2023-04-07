#ifndef __EPOLLHEAP_H__
#define __EPOLLHEAP_H__

#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/socket.h>
#include <sys/epoll.h>
#include <arpa/inet.h>
#include <fcntl.h>
#include <time.h>
#include <errno.h>
#include "chttp.h"

#define MAX_EVENTS 65535 /*监听上限*/
// #define BUFLEN 4096      /*缓存区大小*/
// #define SERV_PORT 6666  /*端口号*/

/*描述就绪文件描述符的相关信息*/
struct myevent_t
{
    int fd;                                           // 要监听的文件描述符
    int events;                                       // 对应的监听事件，EPOLLIN和EPLLOUT
    void *arg;                                        // 指向自己结构体指针
    void (*call_back)(int fd, int events, void *arg); // 回调函数
    int status;                                       // 是否在监听:1->在红黑树上(监听), 0->不在(不监听)
    char buf[BUFSIZ];
    int len;
    long last_active; // 记录每次加入红黑树 g_efd 的时间值
};

// 全局变量 定义在epollheap.h中 epoll_create的返回值
extern struct myevent_t g_myevents[MAX_EVENTS + 1];
extern int g_efd; // 红黑树根

void event_set(struct myevent_t *ev, int fd,
               void (*call_back)(int fd, int events, void *arg), void *arg);

void event_add(int efd, int events, struct myevent_t *ev);

void event_del(int efd, struct myevent_t *ev);

void event_accept_conn(int lfd, int events, void *arg);

void event_recv_data(int fd, int events, void *arg);

void event_send_data(int fd, int events, void *arg);

int event_init(int efd, short port, struct myevent_t *myevents);

#endif