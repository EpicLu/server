#ifndef __EPOLLHEAP_H__
#define __EPOLLHEAP_H__

#include <string.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/socket.h>
#include <sys/epoll.h>
#include <arpa/inet.h>
#include <fcntl.h>
#include <time.h>
#include <ctype.h>
#include <errno.h>

#define MAX_EVENTS 1024 /*监听上限*/
#define BUFLEN 4096     /*缓存区大小*/
#define SERV_PORT 6666  /*端口号*/

/*描述就绪文件描述符的相关信息*/
struct myevent_s
{
    int fd;                                           // 要监听的文件描述符
    int events;                                       // 对应的监听事件，EPOLLIN和EPLLOUT
    void *arg;                                        // 指向自己结构体指针
    void (*call_back)(int fd, int events, void *arg); // 回调函数
    int status;                                       // 是否在监听:1->在红黑树上(监听), 0->不在(不监听)
    char buf[BUFLEN];
    int len;
    long last_active; // 记录每次加入红黑树 g_efd 的时间值
};

extern int g_efd;                                 // 全局变量，作为红黑树根
extern struct myevent_s g_events[MAX_EVENTS + 1]; // 自定义结构体类型数组. +1-->listen fd

void event_set(struct myevent_s *ev, int fd,
               void (*call_back)(int fd, int events, void *arg), void *arg);

void event_add(int efd, int events, struct myevent_s *ev);

void event_del(int efd, struct myevent_s *ev);

void event_acceptconn(int lfd, int events, void *arg);

void event_del(int efd, struct myevent_s *ev);

void event_acceptconn(int lfd, int events, void *arg);

void event_recvdata(int fd, int events, void *arg);

void event_senddata(int fd, int events, void *arg);

void event_init(int efd, short port);

#endif