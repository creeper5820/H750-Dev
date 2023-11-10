#include "main.h"
#include "cmsis_os.h"
#include "gpio.h"

extern "C" {
void BoardLedLoop();
}

void BoardLedLoop()
{
    while (1) {
        osDelay(500);
        HAL_GPIO_WritePin(board_led_GPIO_Port, board_led_Pin, GPIO_PIN_SET);
        osDelay(500);
        HAL_GPIO_WritePin(board_led_GPIO_Port, board_led_Pin, GPIO_PIN_RESET);
    }
}
