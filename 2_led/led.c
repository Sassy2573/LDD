/*
 * @Author: Sassy2573 chenyinlin0429@gmail.com
 * @Date: 2024-08-15 01:36:53
 * @LastEditors: Sassy2573 chenyinlin0429@gmail.com
 * @LastEditTime: 2024-08-24 23:54:04
 * @FilePath: /code/Driver_Development/2_led/led.c
 * @Description: 
 */
#include <linux/types.h>
#include <linux/kernel.h>
#include <linux/delay.h>
#include <linux/ide.h>
#include <linux/init.h>
#include <linux/module.h>
#include <linux/errno.h>
#include <linux/gpio.h>
#include <asm/mach/map.h>
#include <asm/uaccess.h>
#include <asm/io.h>

#define LED_MAJOR 200  /* 主设备号 */
#define LED_NAME "led" /* 设备名 */

#define LEDOFF 0 /* 关灯 */
#define LEDON 1  /* 开灯 */

/* 寄存器物理地址 */
#define CCM_CCGR1_BASE (0X020C406C)
#define SW_MUX_GPIO1_IO03_BASE (0X020E0068)
#define SW_PAD_GPIO1_IO03_BASE (0X020E02F4)
#define GPIO1_DR_BASE (0X0209C000)
#define GPIO1_GDIR_BASE (0X0209C004)

/* 映射后寄存器虚拟地址指针 */
static void __iomem *IMX6U_CCM_CCGR1;
static void __iomem *SW_MUX_GPIO1_IO03;
static void __iomem *SW_PAD_GPIO1_IO03;
static void __iomem *GPIO1_DR;
static void __iomem *GPIO1_GDIR;

/**
 * @description: LED打开/关闭
 * @param {u8} sta 0 打开LED 1 关闭LED
 * @return {*}
 */
void led_switch(u8 sta)
{
    u32 val = 0;
    if (sta == LEDON)
    {
        val = readl(GPIO1_DR);
        val &= ~(1 << 3);
        writel(val, GPIO1_DR);
    }
    else if (sta == LEDOFF)
    {
        val = readl(GPIO1_DR);
        val |= (1 << 3);
        writel(val, GPIO1_DR);
    }
}

/**
 * @description: 打开设备
 * @param {inode} *inode 传递给驱动的inode
 * @param {file} *filp 设备文件
 * @return {*}
 */
static int led_open(struct inode *inode, struct file *filp)
{
    return 0;
}

/**
 * @description: 从设备读取数据
 * @param {file} *filp 要打开的设备文件
 * @param {char __user} *buf 返回给用户空间的数据缓冲
 * @param {size_t} cnt 要读取的数据长度
 * @param {loff_t} *offt 相对于文件首地址的偏移
 * @return {*} 读取的字节数
 */
static ssize_t led_read(struct file *filp, char __user *buf, size_t cnt, loff_t *offt)
{
    return 0;
}

static ssize_t led_write(struct file *filp, const char __user *buf, size_t cnt, loff_t *offt)
{
    int retvalue;
    unsigned char databuf[1];
    unsigned char ledstat;

    retvalue = copy_from_user(databuf, buf, cnt);
}