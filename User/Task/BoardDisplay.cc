#include "main.h"
#include "cmsis_os.h"
#include "gpio.h"
#include "tim.h"

#include "Display.hh"

extern "C" {
void BoardDisplayLoop();
}

void BoardDisplayLoop()
{
    Display display;

    display.InitCs(LCD_CS_GPIO_Port, LCD_CS_Pin);
    display.InitRs(LCD_RS_GPIO_Port, LCD_RS_Pin);
    display.InitTim(&htim1, TIM_CHANNEL_2);
    display.InitSpi(&hspi4);

    display.Init();

    while (1) {

        display.SetBrightness(0.5);
        osDelay(100);
    }
}