#include "chttp.h"

const char *http_get_type(int fd, char *type)
{
    char buf[BUFLEN];
    while (http_get_line(fd, buf, sizeof(buf)) > 1)
    {
        char tmp1[256], tmp2[256];
        if (sscanf(buf, "%[^ ] %[^\\r,;]", tmp1, tmp2) > 0)
            if (strncmp(tmp1, "Accept: ", 7) == 0) // 判断成功后tmp2保存的将是正确的文件类型
            {
                type = tmp2;
                break;
            }
    }
    // type[strlen(type) + 1] = '\0';

    return type;
}