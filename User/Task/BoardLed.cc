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
        HAL_GPIO_TogglePin(LED_GPIO_Port, LED_Pin);
    }
}
