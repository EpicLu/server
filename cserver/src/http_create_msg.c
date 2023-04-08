#include "chttp.h"

int http_create_msg(char *buf, int no, const char *status,
                    const char *file, long size)
{

    sprintf(buf, "HTTP/1.1 %d %s\r\n", no, status);
    sprintf(buf + strlen(buf), "Content-Type: %s\r\n", http_get_type(file));
    sprintf(buf + strlen(buf), "Content-Length: %ld\r\n", size);
    sprintf(buf + strlen(buf), "Connection: close\r\n");
    sprintf(buf + strlen(buf), "\r\n");

    return strlen(buf);
}