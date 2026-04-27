#ifndef USEFONT_H
#define USEFONT_H

#include "font.h"
#include <string.h>

/**
 * @name       font_usefont
 * @brief      LCD font  LCD 字体
 * @param      
 *             @lcd_mp    lcd mapping lcd映射
 *             @str       text to write 写入文字
 *             @Font_Size font size 字体大小
 *			   @bmWith   canvas width  画布宽度
 *             @bmHeight canvas height  画布高度
 * 			   @bmcolorA canvas color A  画布颜色A
 *             @bmcolorR canvas color R  画布颜色R	
 *             @bmcolorG canvas color G  画布颜色G
 *             @bmcolorB canvas color B 画布颜色B
 *			   @ftcolorA text color A  文字颜色A
 *             @ftcolorR text color R  文字颜色R
 *             @ftcolorG text color G  文字颜色G
 *             @ftcolorB text color B  文字颜色B	
 *		       @s32 lcdst_x start position x 起始位置x
 *             @s32 lcdst_y start position y 起始位置y
 * @retval     none
 * @date       2026/04/20
 * @version    1.0
 * @note       
 */
void font_usefont(int *lcd_mp,const char *str, s32 Font_Size,
				  s32 bmWith, s32 bmHeight, 
				  s32 bmcolorA, s32 bmcolorR, s32 bmcolorG,s32 bmcolorB,
				  s32 ftcolorA, s32 ftcolorR, s32 ftcolorG,s32 ftcolorB,
				  s32 lcdst_x, s32 lcdst_y
				);      

#endif // USEFONT_H