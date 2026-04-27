#ifndef TS_TASK_H
#define TS_TASK_H

#include <pthread.h>     //关于线程API接口的头文件   编译时需要指定  -pthread
#include "ts.h"          // 提供 ts_getVal、ts_init 等
#include "log.h"         // 可选，用于日志
#include <stdio.h>
#include <unistd.h>

// 全局变量声明（供外部使用）
extern int ts_fd;               // 触摸屏设备文件描述符
extern int ts_x;                // 最近一次触摸的 X 坐标
extern int ts_y;                // 最近一次触摸的 Y 坐标
extern volatile int touch_pending;   // 是否有新触摸事件
extern pthread_mutex_t touch_mutex;  // 保护共享变量的互斥锁

// 线程函数
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
void *ts_task(void *arg);

#endif // TS_TASK_H