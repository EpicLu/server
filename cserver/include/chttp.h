#ifndef __CHTTP_H__
#define __CHTTP_H__

#include <sys/stat.h>
#include <pthread.h>
#include "epollheap.h"

struct http_myevent_t
{
    struct myevent_t mev;
    pthread_mutex_t lock; // 封装myevent_t结构体配把锁 用于服务端保证先发报文再发数据
};

// 全局变量
extern struct http_myevent_t g_hev[MAX_EVENTS + 1];

int http_create_msg(char *buf, int no, const char *status,
                    const char *file, long size);

int http_event_init(int efd, short port, struct http_myevent_t *hev);

int http_get_line(int cfd, char *buf, int size);

void http_event_accept(int lfd, int events, void *arg);

void http_send_file(int cfd, int events, void *arg);

void http_recv_msg(int cfd, int events, void *arg);

void http_send_msg(int cfd, int events, void *arg);

void http_response(int cfd, char *file, void *arg);

const char *http_get_type(const char *file);

#endif