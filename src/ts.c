#include "ts.h"

/**
 * @name       ts_init
 * @brief      ts initialization LCD初始化
 * @param      
 *             @lcd_path Path of ts driver ts驱动的路径
 * @retval     int   ts file descriptors.   ts文件描述符
 * @date       2026/04/19
 * @version    1.0
 * @note       
 */
int ts_init(const char *ts_path)
{
    //1.打开触摸屏
    int ts_fd = open(ts_path,O_RDWR);
    if (-1 == ts_fd)
    {
        errorPrint("error ts -1");
        return -1;
    }
    return ts_fd;
}

/**
 * @name       ts_getVal
 * @brief      ts get coord   ts 获取坐标
 * @param      
 *             @fd file descriptors. 文件描述符
 *             @fd_x coord of x x的坐标
 *             @fd_y coord of y y的坐标
 * @retval     none
 * @date       2026/04/19
 * @version    1.0
 * @note       
 */
void ts_getVal(int fd, int *fd_x, int *fd_y)
{
    int cnt = 0;
    //2.获取输入设备的信息
    struct input_event ts_event;

    read(fd,&ts_event,sizeof(ts_event));

    //3.分析读取的设备信息（type + code + value）
    if (ts_event.type == EV_ABS) //说明是触摸屏
    {
        if (ts_event.code == ABS_X)
        {
            cnt++;
            *fd_x = ts_event.value * lcdwidth / tswidth;
        }
        if (ts_event.code == ABS_Y)
        {
            cnt++;
            *fd_y = ts_event.value * lcdheight / tsheight;
        }

        if (cnt >= 2)
        {
            cnt = 0;
        }    
    }
}

//用户点击触摸屏
/**
 * @name       SelectedLcd
 * @brief      user click LCD   用户点击LCD
 * @param      
 *             @merchant merchant coord 商家坐标
 *             @user user coord 用户坐标
 * @retval     none
 * @date       2026/04/23
 * @version    1.0
 * @note       
 */
int SelectedLcd(coord_t *merchant, coord_t *user)
{
    LogPrint("Waiting for user selection");
    int selected = 0;
    while (!selected) {
        int x = 0, y = 0;
        pthread_mutex_lock(&touch_mutex);
        if (touch_pending) {
            x = ts_x;
            y = ts_y;
            touch_pending = 0;
        }
        pthread_mutex_unlock(&touch_mutex);

        if (x != 0 || y != 0)
        {
            printf("Touch at (x = %d, y = %d)", x, y);
            // 根据选择界面的按钮区域判断（示例坐标，请根据实际界面修改）
            if (x >= merchant->start_x && x <= merchant->end_x && y >= merchant->start_y && y <= merchant->end_y) 
            {
                LogPrint("Charging pile 1 selected");
                selected = 1;
                return 1;
            } else if (x >= user->start_x && x <= user->end_x && y >= user->start_y && y <= user->end_y) 
            {
                LogPrint("Charging pile 2 selected");
                selected = 1;
                return 2;
            } else {
                LogPrint("Invalid area, continue waiting");
            }
        }
        usleep(50000);  // 50ms 轮询
    }
}

/**
 * @name       ts_uninit
 * @brief      ts uninitialization LCD解除初始化
 * @param      
 *             @fd file descriptors. 文件描述符
 * @retval     none
 * @date       2026/04/19
 * @version    1.0
 * @note       
 */
void ts_uninit(int fd)
{
    close(fd);
}