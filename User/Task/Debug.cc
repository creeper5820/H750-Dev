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
    ValueManager value;

    value.New("VALUE", (float)12.5);

    while (1) {
        // serial.HelloWorld(1);
        osDelay(1000);
    }
}