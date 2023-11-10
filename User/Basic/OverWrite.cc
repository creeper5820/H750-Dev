/**
 * @author creeper5820
 * @brief 各种中断处理函数的复写区域
 */

#include "main.h"
#include "cmsis_os.h"

extern "C" {
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart);
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin);
}

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
}

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
    if (GPIO_Pin == board_key_Pin) {
    }
}