#include "main.h"
#include "cmsis_os.h"
#include "gpio.h"

#include "SerialManager.hh"

extern "C" {
void DebugLoop();
}

void DebugLoop()
{
    while (1) {
        osDelay(100);
    }
}