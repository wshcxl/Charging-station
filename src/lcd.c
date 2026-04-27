#include "lcd.h"

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
LcdDev_t *lcd_init(const char *lcd_path)
{
    //1.申请堆内存
    LcdDev_t *lcd = (LcdDev_t *)calloc(1,sizeof(LcdDev_t));

    //*lcd是结构体本身，不能用来判断，lcd即是结构体的地址
    if (lcd == NULL)
    {
        errorPrint("calloc lcd NUll");
        return NULL;
    }
    //应该是lcd_path而不是*lcd_path，是因为带*号即意味着是传入第一个的字符
    lcd->fd = open(lcd_path,O_RDWR);
    if (-1 == lcd->fd)
    {
        errorPrint("lcd->fd error");
        return NULL;
    }

    lcd->mp = (int *)mmap(NULL,
                          LCD_MAPSIZE,
                          PROT_READ|PROT_WRITE,
                          MAP_SHARED,
                          lcd->fd,
                          0
                         ); 
    if (lcd->mp == MAP_FAILED) {
       errorPrint("lcd->mp error");
       return NULL; 
    }
    
    return lcd;
}

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
void lcd_clear(unsigned int *lcd_mp, unsigned int color) 
{
    for (int i = 0; i < 800 * 480; i++) {
        lcd_mp[i] = color;
    }
}

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
void lcd_fill_rect(unsigned int *lcd_mp, int x, int y, int w, int h, unsigned int color) 
{
    // 裁剪：确保矩形不超出屏幕边界
    int start_x = (x < 0) ? 0 : x;
    int start_y = (y < 0) ? 0 : y;
    int end_x = (x + w > SCREEN_W) ? SCREEN_W : x + w;
    int end_y = (y + h > SCREEN_H) ? SCREEN_H : y + h;

    for (int row = start_y; row < end_y; row++) {
        unsigned int *dst = lcd_mp + row * SCREEN_W + start_x;
        for (int col = start_x; col < end_x; col++) {
            *dst++ = color;
        }
    }
}

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
void lcd_uninit(LcdDev_t *Lcd)
{
    if (Lcd == NULL)
    {
        errorPrint("uninit Lcd NULL");
        return;
    }

    //解除内存映射
    if (NULL != Lcd->mp)
    {
        munmap(Lcd->mp, LCD_MAPSIZE);
    }
    
    //关闭LCD屏 
    if (-1 != Lcd->fd)
    {
        close(Lcd->fd);
    }

    free(Lcd);

    //指针置空
    Lcd = NULL;
}