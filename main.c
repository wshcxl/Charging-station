//arm-linux-gcc main.c ./src/*.c -o ./bin/main -I ./include/ -L ./lib/ -ljpeg -lfont -lm -pthread
#include "lcd.h"
#include "ts.h"
#include "jpeg.h"
#include "usefont.h"
#include "log.h"
#include "login.h"
#include "interfaceui.h"
#include "ts_task.h"  //关于线程API接口的头文件   编译时需要指定  -pthread

int main(int argc, char const *argv[])
{
	//1.LCD屏初始化
	LogPrint("LCDinit");
	LcdDev_t *lcdDev = lcd_init(LCD_PATH);

	// 清屏为黑色（0xFF000000 为不透明黑色）
	lcd_clear(lcdDev->mp, 0xFF000000);

	//2.触摸屏初始化
	LogPrint("TSinit");
	ts_fd = ts_init(TsPath);

	//3.创建子线程
	LogPrint("ts_thread init");
    pthread_t ts_thread;
    pthread_create(&ts_thread,NULL,ts_task,NULL);

	//4.系统开机动画
	if (NULL != lcdDev)
	{
		LogPrint("jpegShow");
		BootAnimation(lcdDev);
	}

	// 清屏为白色（0xFFFFFFFF 为不透明白色）
	lcd_clear(lcdDev->mp, 0xFFFFFFFF);

	//5.共享充电桩选择界面
	LogPrint("SelectionInterface");
	SelectionInterface(lcdDev);
    //商家
	coord_t merchant;
	merchant.start_x = 270;
	merchant.end_x = 355;
	merchant.start_y = 350;
	merchant.end_y = 370;

    //用户
	coord_t user;
	user.start_x = 445;
	user.end_x = 530;
	user.start_y = 350;
	user.end_y = 370;

	//6.等待用户点击  1为商家 2为用户 商家端不实现
	int userclick = SelectedLcd(&merchant,&user);
	if (2 != userclick)
	{
		LogPrint("click error");
		return -1;
	}
	//7.跳转登录界面
	LogPrint("LoginInterface");
	LoginInterface(lcdDev);

	//6.等待用户点击  1为注册 2为登录 因为是一张图片，可以共用
	int loginclick = SelectedLcd(&merchant,&user);
	if (1 == loginclick)
	{
		//注册
		login(lcdDev);
	}else if ( 2 == loginclick)
	{
		//登录
		logregister();
	}
	
	
	

    if (-1 != ts_fd)
	{
		LogPrint("ts_uninit");
		ts_uninit(ts_fd);
	}
	
	LogPrint("lcd_uninit");
	lcd_uninit(lcdDev);

	return 0;
}



