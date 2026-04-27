#include "usefont.h"
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
 *             @bmcolorR canvas color B  画布颜色B	
 *             @bmcolorG canvas color G  画布颜色G
 *             @bmcolorB canvas color R 画布颜色R
 *			   @ftcolorA text color A  文字颜色A
 *             @ftcolorR text color B  文字颜色B
 *             @ftcolorG text color G  文字颜色G
 *             @ftcolorB text color R  文字颜色R	
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
				)
{
	//1.打开开发板路径下TrueType字库
	font *f = fontLoad("./font/simkai.ttf");

	//2.字体大小的设置
	fontSetSize(f,Font_Size);
	
	//3.创建一个画板（点阵图）
	bitmap *bm = createBitmapWithInit(bmWith,bmHeight,4,getColor(bmcolorA,bmcolorB,bmcolorG,bmcolorR)); //也可使用createBitmapWithInit函数，改变画板颜色
	
	// char buf[] = str;  不行
	char buf[256];   // 假设最大长度 256
	strcpy(buf, str);
	
	//6.将字体写到点阵图上
	fontPrint(f,bm,0,0,buf,getColor(ftcolorA,ftcolorB,ftcolorG,ftcolorR),0);
	
	//7.把字体框输出到LCD屏幕上
	show_font_to_lcd(lcd_mp,lcdst_x,lcdst_y,bm);

	//8.关闭字体库
	fontUnload(f);

	//9.关闭bitmp
	destroyBitmap(bm);

	
	return;
}

/*

	两个函数可以只用一个
	// 创建一个 800x480 的 ARGB 画布（不初始化）
	bitmap *bm1 = createBitmap(800, 480, 4);
	// 然后绘制文字，文字颜色为白色，背景透明或需要自己填充背景

	// 创建一个带蓝色背景的画布
	bitmap *bm2 = createBitmapWithInit(800, 480, 4, 0xFF0000FF); // 蓝色背景
	// 然后在上面绘制文字，文字会显示在蓝色背景上


*/