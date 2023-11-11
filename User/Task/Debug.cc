#include "main.h"
#include "cmsis_os.h"
#include "gpio.h"

#include "SerialManager.hh"
#include "ValueManager.hh"

extern "C" {
void DebugLoop();
}

void DebugLoop()
{
    SerialManager serial(&huart4);

    while (1) {
        osDelay(100);
    }
}