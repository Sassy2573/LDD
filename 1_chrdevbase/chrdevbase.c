/*
 * @Author: Sassy chenyinlin0429@gmail.com
 * @Date: 2024-07-31 02:50:14
 * @LastEditors: Sassy2573 chenyinlin0429@gmail.com
 * @LastEditTime: 2024-08-15 01:22:45
 * @FilePath: /1_chrdevbase/chrdevbase.c
 * @Description: chrdevbase 驱动文件
 *
 * Copyright (c) 2024 by ${git_name_email}, All Rights Reserved.
 */
#include <linux/types.h>
#include <linux/kernel.h>
#include <linux/delay.h>
#include <linux/ide.h>
#include <linux/init.h>
#include <linux/module.h>

#define CHRDEVBASE_MAJOR 200         // 主设备号
#define CHRDEVBASE_NAME "chrdevbase" // 设备名称

static char readbuf[100];  // 读缓冲区
static char writebuf[100]; // 写缓冲区
static char kerneldata[] = {"kernel data!"};

/**
 * @description: 打开设备
 * @param {inode} *inode 传递给驱动的inod
 * @param {file} *file  设备文件，一般在open的时候将private_data指向设备结构体
 * @return {*} 0成功，其他失败
 */
static int chrdevbase_open(struct inode *inode, struct file *file)
{
    printk("chrdevbase open\n");
    return 0;
}

static ssize_t chrdevbase_read(struct file *filp, char __user *buf, size_t cnt, loff_t *offt)
{
    int retvalue = 0;

    /* 向用户空间发送数据 */
    memcpy(readbuf, kerneldata, sizeof(kerneldata));
    /* 将数据从内核空间复制到用户空间  buf：用户空间 readbuf：内核空间中的缓冲区指针 */
    retvalue = copy_to_user(buf, readbuf, cnt);  
    if (retvalue == 0)
    {
        printk("kernel send data ok!\r\n");
    }
    else
    {
        printk("kernel senddata failed!\r\n");
    }

    return 0;
}

/**
 * @description: 向设备写数据
 * @param {file} *filp  设备文件，表示打开的文件描述符
 * @param {char __user} *buf    要写入的用户空间数据
 * @param {size_t} cnt  要写入的数据大小
 * @param {loff_t} *offt    相对于文件开头的偏移
 * @return {*} 写入的字节数，负数表示失败
 */
static ssize_t chrdevbase_write(struct file *filp, const char __user *buf, size_t cnt, loff_t *offt)
{
    int retvalue = 0;
    /* 从用户空间接收数据 */
    retvalue = copy_from_user(writebuf, buf, cnt);
    if (retvalue == 0)
    {
        printk("kernel recvdata:%s\r\n", writebuf);
    }
    else
    {
        printk("kernel recvdata failed!\r\n");
    }
    return 0;
}

/**
 * @description: 关闭/释放设备
 * @param {inode} *inode
 * @param {file} *file 要关闭的设备文件（文件描述符）
 * @return {*} 0成功，其他失败
 */
static int chrdevbase_release(struct inode *inode, struct file *file)
{
    printk("chrdevbase release\n");
    return 0;
}

/**
 * 设备操作函数结构体
 */
static struct file_operations chrdevbase_fops = {
    .owner = THIS_MODULE,
    .open = chrdevbase_open,
    .read = chrdevbase_read,
    .write = chrdevbase_write,
    .release = chrdevbase_release,
};

/**
 * @description: 驱动入口函数
 * @return {*} 0成功，其他失败
 */
static int __init chrdevbase_init(void)
{
    int retvalue = 0;

    /* 注册字符设备驱动 */
    /* major：主设备号   name：设备名字 */
    retvalue = register_chrdev(CHRDEVBASE_MAJOR, CHRDEVBASE_NAME, &chrdevbase_fops);
    
    if (retvalue < 0)
    {
        /* 注册失败 */
        printk("chrdevbase driver register failed!\r\n");
    }   
    printk("chrdevbase_init()\r\n");
    return 0;
}

/**
 * @description: 驱动出口函数
 * @return {*}
 */
static void __exit chrdevbase_exit(void)
{
    /* 注销字符设备驱动 */
    unregister_chrdev(CHRDEVBASE_MAJOR, CHRDEVBASE_NAME);
    printk("chrdevbase_exit()\r\n");
}

/* 将上方两个函数指定为驱动的入口和出口函数 */
module_init(chrdevbase_init);
module_exit(chrdevbase_exit);

/* 
    LICENSE和作者信息
 */
MODULE_LICENSE("GPL");
MODULE_AUTHOR("chenyinlin");