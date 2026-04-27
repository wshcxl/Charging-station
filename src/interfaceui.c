#include "interfaceui.h"

/**
 * @name       BootAnimation
 * @brief      Boot Animation Boot Animation 开机动画
 * @param      
 *             @lcdDev LCD device information lcd设备信息
 * @retval     none
 * @date       2026/04/21
 * @version    1.0
 * @note       
 */
void BootAnimation(LcdDev_t *lcdDev)
{
   jpegShow(lcdDev->mp, 0, 40); 
}

/**
 * @name       SelectionInterface
 * @brief      Selection Interface Selection Interface 选择界面
 * @param      
 *             @lcdDev LCD device information lcd设备信息
 * @retval     none
 * @date       2026/04/21
 * @version    1.0
 * @note       
 */
void SelectionInterface(LcdDev_t *lcdDev)
{
    LogPrint("jpeg_to_lcd");
	jpeg_to_lcd(lcdDev->mp, "./gif/icon.jpg", 200, 150);

    //5.显示文字界面
	LogPrint("font_usefont");
    font_usefont(lcdDev->mp,"共享充电桩系统",
	            32,         //字体大小
				250,50,
	            0,255,255,255,
				255,0,0,0,
				300,50);
    font_usefont(lcdDev->mp,"我是商家",
				22,      //字体大小
				85,20,   //宽度高度
				0,236,237,239,
				255,0,0,0,
				270,350);  //起始位置
    font_usefont(lcdDev->mp,"我是用户",
				22,       //字体大小
				85,20,   //宽度高度
				0,236,237,239,
				255,0,0,0,
				445,350);  //起始位置
}

/**
 * @name       Login Interface
 * @brief      Login Interface 登录界面
 * @param      
 *             @lcdDev LCD device information lcd设备信息
 * @retval     none
 * @date       2026/04/23
 * @version    1.0
 * @note       
 */
void LoginInterface(LcdDev_t *lcdDev)
{
    LogPrint("jpeg_to_lcd");
	// 清屏为白色（0xFFFFFFFF 为不透明白色）
	lcd_clear(lcdDev->mp, 0xFFFFFFFF);
	jpeg_to_lcd(lcdDev->mp, "./gif/icon.jpg", 200, 150);

    //5.显示文字界面
	LogPrint("font_usefont");
    font_usefont(lcdDev->mp,"共享充电桩系统",
	            32,         //字体大小
				250,50,
	            0,255,255,255,
				255,0,0,0,
				300,50);
    font_usefont(lcdDev->mp,"注册账号",
				22,      //字体大小
				85,20,   //宽度高度
				0,236,237,239,
				255,0,0,0,
				270,350);  //起始位置
    font_usefont(lcdDev->mp,"登录账号",
				22,       //字体大小
				85,20,   //宽度高度
				0,236,237,239,
				255,0,0,0,
				445,350);  //起始位置
}

void showLogin(LcdDev_t *lcdDev)
{
    LogPrint("showLogin");
	// 清屏为白色（0xFFFFFFFF 为不透明白色）
	lcd_clear(lcdDev->mp, 0xFFFFFFFF);
	// 在需要的位置调用
    lcd_fill_rect(lcdDev->mp, 200, 150, 400, 225, 0xFF808080);  // 灰色

    //5.显示文字界面
	LogPrint("font_usefont");
	char digit[2];
	for (int i = 1;i <= 9;i++)
	{
		int w_a = 0;
		int h_a = 0;
		if ((i == 3) || (i == 6) )
		{
			w_a = 0;
			h_a *=10;
		}
		digit[0] = '0' + i;
		digit[1] = '\0';
		font_usefont(lcdDev->mp, digit,
			20,         //字体大小
			250,50,
			0,255,255,255,
			255,0,0,0,
			300 + w_a * 10,50 + h_a);
		w_a++;
	}
}