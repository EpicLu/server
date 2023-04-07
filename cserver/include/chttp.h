#ifndef __CHTTP_H__
#define __CHTTP_H__

#include <sys/stat.h>
#include "epollheap.h"

void http_request(int cfd, const char *file, void *arg);

int http_get_line(int cfd, char *buf, int size);

const char *http_get_type(int fd, char *type);

#endif