#include "chttp.h"

// 获取http请求的文件类型
const char *http_get_type(const char *file)
{
    char *dot;
    dot = strrchr(file, '.');

    if (dot == NULL)
        return "text/plain; charset=utf-8";
    if (strcmp(dot, ".html") == 0 || strcmp(dot, ".htm") == 0)
        return "text/html; charset=utf-8";
    if (strcmp(dot, ".jpg") == 0 || strcmp(dot, ".jpeg") == 0)
        return "image/jpeg";
    if (strcmp(dot, ".gif") == 0)
        return "image/gif";
    if (strcmp(dot, ".png") == 0)
        return "image/png";
    if (strcmp(dot, ".css") == 0)
        return "text/css";
    if (strcmp(dot, ".au") == 0)
        return "audio/basic";
    if (strcmp(dot, ".wav") == 0)
        return "audio/wav";
    if (strcmp(dot, ".avi") == 0)
        return "video/x-msvideo";
    if (strcmp(dot, ".mov") == 0 || strcmp(dot, ".qt") == 0)
        return "video/quicktime";
    if (strcmp(dot, ".mpeg") == 0 || strcmp(dot, ".mpe") == 0)
        return "video/mpeg";
    if (strcmp(dot, ".vrml") == 0 || strcmp(dot, ".wrl") == 0)
        return "model/vrml";
    if (strcmp(dot, ".midi") == 0 || strcmp(dot, ".mid") == 0)
        return "audio/midi";
    if (strcmp(dot, ".mp3") == 0)
        return "audio/mpeg";
    if (strcmp(dot, ".ogg") == 0)
        return "application/ogg";
    if (strcmp(dot, ".pac") == 0)
        return "application/x-ns-proxy-autoconfig";
    if (strcmp(dot, ".tof") == 0 || strcmp(dot, ".ttf") == 0 || strcmp(dot, ".woff2") == 0 || strcmp(dot, ".woff") == 0)
        return "application/octet-stream";
    /*if (strcmp(dot, ".woff") == 0)
        return "application/x-font-woff";*/
    if (strcmp(dot, ".svg") == 0)
        return "image/svg+xml";
    if (strcmp(dot, ".js") == 0)
        return "application/x-javascript";
    /*if (strcmp(dot, ".woff2") == 0)
        return "application/font-woff2";*/
    if (strcmp(dot, ".ico") == 0)
        return "image/ico";
    if (strcmp(dot, ".mp4"))
        return "video/mp4";

    return "text/plain; charset=utf-8";
}