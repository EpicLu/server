#ifndef __CHTTP_H__
#define __CHTTP_H__

#include <sys/stat.h>

#include "epollheap.h"

int http_get_line(int cfd, char *buf, int size);

int http_send_file(int cfd, const char *file);

int http_event_init(int efd, short port, struct myevent_t *myevents);

const char *http_get_type(const char *file);

void http_response(int cfd, char *file, void *arg);

void http_event_accept(int lfd, int events, void *arg);

void http_recv_msg(int cfd, int events, void *arg);

void http_send_msg(int cfd, int events, void *arg);

#endif