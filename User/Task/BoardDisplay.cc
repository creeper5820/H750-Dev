#include "main.h"
#include "cmsis_os.h"
#include "gpio.h"
#include "tim.h"

extern "C" {
void BoardDisplayLoop();
}

void BoardDisplayLoop()
{
    HAL_TIMEx_PWMN_Start(&htim1, TIM_CHANNEL_2);

    while (1) {
        __HAL_TIM_SetCompare(&htim1, TIM_CHANNEL_2, 500);

        osDelay(100);
    }
}