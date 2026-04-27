/**            
 * @file       jpeg.h   
 * @brief      lcd show jpeg        
 * @author     2475232977@qq.com
 * @date       2026/04/19
 * @version    1.0
 * @property   
 * @note       
 * @copyright  Copyright (c)   2026    2475232977@qq.com    All Right Reseverd
 */

#ifndef _jpeg_H
#define _jpeg_H

#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <unistd.h>
#include "log.h"
#include "jpeglib.h"

#define jpegcount 54

/**
 * @name       jpegShow
 * @brief      jpeg Show jpeg显示
 * @param      
 *             @lcd_mp  Mapping space 映射空间
 *             @x  start x
 *             @y  start y 
 * @retval     none
 * @date       2026/04/19
 * @version    1.0
 * @note       
 */
void jpegShow(int *lcd_mp, int x, int y);

/**
 * @name       jpeg_to_lcd
 * @brief      jpeg show lcd LCD显示图片
 * @param      
 *             @lcd_mp  Mapping space 映射空间
 *             @jpegpath jieg path 
 *             @start_x  start x
 *             @start_y  start y 
 * @retval     none
 * @date       2026/04/19
 * @version    1.0
 * @note       
 */
bool jpeg_to_lcd(int *lcd_mp, const char* jpegpath, int start_x, int start_y);


#endif