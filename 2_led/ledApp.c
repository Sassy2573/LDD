/*
 * @Author: chen chenyinlin0429@gmail.com
 * @Date: 2024-08-25 15:37:10
 * @LastEditors: chen chenyinlin0429@gmail.com
 * @LastEditTime: 2024-08-25 15:42:22
 * @FilePath: /LDD/2_led/ledApp.c
 * @Description: 这是默认设置,请设置`customMade`, 打开koroFileHeader查看配置 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
 */
#include "stdio.h"
#include "unistd.h"
#include "sys/types.h"
#include "sys/stat.h"
#include "fcntl.h"
#include "stdlib.h"
#include "string.h"

#define LEDOFF 0
#define LEDON 1

int main(int argc, char *argv[])
{
    int fd, retvalue;
    char *filename;
    unsigned char databuf[1];

    if (argc != 3)
    {
        printf("Error Usage!\r\n");
        return -1;
    }

    filename = argv[1];

    fd = open(filename, O_RDWR);
    if (fd < 0)
    {
        printf("file %s open failed!\r\n", argv[1]);
        return -1;
    }

    databuf[0] = atoi(argv[2]);

    retvalue = write(fd, databuf, sizeof(databuf));
    if (retvalue < 0)
    {
        printf("LED Control Failed!\r\n");
        close(fd);
        return -1;
    }

    retvalue = close(fd);
    if (retvalue < 0)
    {
        printf("file %s close failed!\r\n", argv[1]);
        return -1;
    }
    return 0;

    
    
    
    
}