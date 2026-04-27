#ifndef INTERFACEUI_H
#define INTERFACEUI_H

#include "lcd.h"
#include "ts.h"
#include "jpeg.h"
#include "usefont.h"
#include "log.h"

/**
 * @name       BootAnimation
 * @brief      Boot Animation Boot Animation 开机动画
 * @param      
 *             @lcdDev LCD device information lcd设备信息
 * @retval     none
 * @date       2026/04/19
 * @version    1.0
 * @note       
 */
void BootAnimation(LcdDev_t *lcdDev);

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
void SelectionInterface(LcdDev_t *lcdDev);

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
void LoginInterface(LcdDev_t *lcdDev);

void showLogin(LcdDev_t *lcdDev);

#endif // INTERFACEUI_H