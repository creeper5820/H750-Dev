#include "main.h"
#include "cmsis_os.h"
#include "gpio.h"
#include "tim.h"

extern "C" {
void BoardDisplayLoop();
}

void BoardDisplayLoop()
{

    while (1) {

        osDelay(100);
    }
}