#include "log.h"

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
void errorPrint(const char* str)
{
    if (!g_error_log)
    {
        printf("err_log false"); 
        return;
    }
    printf("errlog: %s",str);
}

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
void LogPrint(const char* str)
{
    if (!g_log_enabled)
    {
        printf("log_enabled false\n"); 
        return;
    }
    
    printf("log: %s\n",str);
    if(!fileLogPrint(str))
    {
        printf("file log error\n");    
    }
}

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
bool fileLogPrint(const char* Filestr)
{
    FILE *file = fopen("log.txt", "ab");
    if (NULL == file)
    {
        perror("log file open error\n"); 
        return false;
    }
    char strtime[400]; 
    struct tm *tminfo;
    time_t Now;

    Now = time(NULL);
    tminfo = localtime(&Now);
    if (NULL == tminfo)
    {
        perror("localtime\n");
        fclose(file);
        return false;
    }
    int len = sprintf(strtime,"%dyear%dmonth%dday %d:%d:%d\n",
                        tminfo->tm_year + 1900,
                        tminfo->tm_mon + 1,
                        tminfo->tm_mday,
                        tminfo->tm_hour,
                        tminfo->tm_min,
                        tminfo->tm_sec);
    //追加内容防止溢出
    strncat(strtime, Filestr, sizeof(strtime) - len - 1);
    // 确保换行（如果原字符串没有）
    if (strtime[strlen(strtime)-1] != '\n')
        strcat(strtime, "\n");
    fprintf(file, "%s", strtime);
    fflush(file);   // 立即将日志写入文件，避免丢失（如程序崩溃时）

    fclose(file);
    return true;
}