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
        HAL_GPIO_WritePin(Led_GPIO_Port, Led_Pin, GPIO_PIN_SET);
        osDelay(500);
        HAL_GPIO_WritePin(Led_GPIO_Port, Led_Pin, GPIO_PIN_RESET);
    }
}
