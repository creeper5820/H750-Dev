/**
 * @author creeper5820
 * @brief 各种中断处理函数的复写区域
 */

#include "main.h"

extern "C" {
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart);
}

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
}