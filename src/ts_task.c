#include "ts_task.h"

// 定义全局变量（唯一定义处）
int ts_fd;
int ts_x;
int ts_y;
volatile int touch_pending = 0;
pthread_mutex_t touch_mutex = PTHREAD_MUTEX_INITIALIZER;

//调用线程
/**
 * @name       ts_task
 * @brief      Thread execution function 线程执行函数
 * @param      
 *             @arg default parameters 默认参数
 * @retval     none
 * @date       2026/04/23
 * @version    1.0
 * @note       
 */
void *ts_task(void *arg) 
{
    LogPrint("ts_thread start");
    while (1) {
        int x, y;
        ts_getVal(ts_fd, &x, &y);
        // 假设 ts_getVal 只在真正触摸时返回有效坐标（0~800, 0~480）
        if (x >= 0 && x < 800 && y >= 0 && y < 480) {
            pthread_mutex_lock(&touch_mutex);
            ts_x = x;
            ts_y = y;
            touch_pending = 1;
            pthread_mutex_unlock(&touch_mutex);
        }
        usleep(10000);  // 10ms 轮询，避免 CPU 空转
    }
    return NULL;
}