/**            
 * @file       log.h   
 * @brief      Log file implementation         
 * @author     2475232977@qq.com
 * @date       2026/04/19
 * @version    1.0
 * @property   
 * @note       
 * @copyright  Copyright (c)   2026    2475232977@qq.com    All Right Reseverd
 */

#ifndef _LOG_H
#define _LOG_H

#include <stdio.h>
#include <stdbool.h>
#include <time.h>
#include <string.h>

static bool g_log_enabled = true;   // 普通日志开关，默认开启
static bool g_error_log = true;   // 错误日志开关，默认开启

/**
 * @name       LogPrint
 * @brief      Printed console display logs and text logs 打印的控制台显示日志与文本的日志
 * @param      
 *             @str print character 要打印的字符
 * @retval     None
 * @date       2026/04/19
 * @version    1.0
 * @note       
 */
void LogPrint(const char* str);

/**
 * @name       fileLogPrint
 * @brief      Printed text logs 打印文本的日志
 * @param      
 *             @Filestr print character 要打印的字符
 * @retval     None
 * @date       2026/04/19
 * @version    1.0
 * @note       
 */
bool fileLogPrint(const char* Filestr);

/**
 * @name       errorPrint
 * @brief      Printed error logs 打印错误的日志
 * @param      
 *             @str print character 要打印的字符
 * @retval     None
 * @date       2026/04/19
 * @version    1.0
 * @note       
 */
void errorPrint(const char* str);

#endif