/**            
 * @file       lcd.h   
 * @brief      LCD screen display  LCD屏显示         
 * @author     2475232977@qq.com
 * @date       2026/04/19
 * @version    1.0
 * @property   
 * @note       
 * @copyright  Copyright (c)   2026    2475232977@qq.com    All Right Reseverd
 */

#ifndef _LCD_H
#define _LCD_H

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <unistd.h>
#include "log.h"

//LCD屏的设备路径，根据实际情况修改
#define  LCD_PATH   "/dev/fb0"

//LCD内存映射的大小
#define  LCD_MAPSIZE (800*480*4)
#define  SCREEN_W  800  // 你的 LCD 实际宽度
#define  SCREEN_H  480  // 你的 LCD 实际高度

typedef struct lcd_deviceinfo
{
    int fd;   //用于记录文件描述符
    int *mp;  //用于记录内存映射
}LcdDev_t;

/**
 * @name       lcd_init
 * @brief      LCD initialization LCD初始化
 * @param      
 *             @lcd_path Path of LCD driver lcd驱动的路径
 * @retval     LcdDev_t * The LCD device information includes file descriptors and memory mapping.   LCD设备信息包含文件描述符与内存映射
 * @date       2026/04/19
 * @version    1.0
 * @note       
 */
LcdDev_t *lcd_init(const char *lcd_path);

/**
 * @name       lcd_clear
 * @brief      LCD clear LCD清屏
 * @param      
 *             @lcd_mp Mapping space 映射空间
 *             @color  color 颜色
 * @retval     none
 * @date       2026/04/19
 * @version    1.0
 * @note       
 */
void lcd_clear(unsigned int *lcd_mp, unsigned int color);

/**
 * @name       lcd_fill_rect
 * @brief      在 LCD 上绘制一个实心矩形
 * @param      lcd_mp      LCD 显存映射指针
 * @param      x           矩形左上角 X 坐标
 * @param      y           矩形左上角 Y 坐标
 * @param      w           矩形宽度（像素）
 * @param      h           矩形高度（像素）
 * @param      color       填充颜色（32位 ARGB）
 */
void lcd_fill_rect(unsigned int *lcd_mp, int x, int y, int w, int h, unsigned int color);

/**
 * @name       lcd_uninit
 * @brief      LCD uninitialization LCD解除初始化
 * @param      
 *             @lcd LCD device information lcd设备信息
 * @retval     none
 * @date       2026/04/19
 * @version    1.0
 * @note       
 */
void lcd_uninit(LcdDev_t *Lcd);

#endif