#include "chttp.h"

int http_compress(void *arg, unsigned char *buf, uLong *buflen)
{
    const char *filename = (char *)arg;
    char zipfile[128];
    strcpy(zipfile, filename);
    strcat(zipfile, ".zip");
    FILE *file;
    uLong flen;
    unsigned char *fbuf = NULL;

    if ((file = fopen(filename, "rb")) == NULL)
    {
        printf("Can\'t open %s!\n", filename);
        return -1;
    }

    /* 装载源文件数据到缓冲区 */
    fseek(file, 0L, SEEK_END); /* 跳到文件末尾 */
    flen = ftell(file);        /* 获取文件长度 */
    fseek(file, 0L, SEEK_SET);
    if ((fbuf = (unsigned char *)malloc(sizeof(unsigned char) * flen)) == NULL)
    {
        printf("No enough memory!\n");
        fclose(file);
        return -1;
    }
    fread(fbuf, sizeof(unsigned char), flen, file);

    /* 压缩数据 */
    if (buf == NULL)
    {
        printf("No enough memory!\n");
        fclose(file);
        return -1;
    }
    if (compress((Bytef *)buf, buflen, (Bytef *)fbuf, flen) != Z_OK)
    {
        printf("Compress %s failed!\n", filename);
        return -1;
    }

    fclose(file);

    if ((file = fopen(zipfile, "wb")) == NULL)
    {
        printf("Can\'t create %s!\n", zipfile);
        return -1;
    }
    /* 保存压缩后的数据到目标文件 */
    // fwrite(&flen, sizeof(uLong), 1, file);   /* 写入源文件长度 */
    // fwrite(&buflen, sizeof(uLong), 1, file); /* 写入目标数据长度 */
    fwrite(buf, sizeof(unsigned char), *buflen, file);

    free(fbuf);
    fclose(file);
    return 0;
}