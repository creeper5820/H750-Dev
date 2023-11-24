#include "main.h"
#include "cmsis_os.h"
#include "gpio.h"

#include "SerialManager.hh"
#include "PwmGenerator.hh"
#include "DataHandler.hh"

extern "C" {
void DebugLoop();
}

bool flag;

uint8_t front[] = { 0xaa, 0xbb, 0xcc };
uint8_t back[] = { 0xcc, 0xbb, 0xaa };
uint8_t data[] = { 0xaa, 0xbb, 0xcc, 11, 23, 54, 35, 0xcc, 0xbb, 0xaa };

int32_t integer;
float floater;

void DebugLoop()
{
    SerialManager serial(&huart4);
    PwmGenerator pwm(&htim1, TIM_CHANNEL_2);
    DataHandler data_handler;

    while (1) {
        data_handler.SetCheckFront(front);
        data_handler.SetCheckBack(back);
        data_handler.Load(data, sizeof(data) / sizeof(data[0]));

        flag = data_handler.IsVaild();

        if (flag) { 
            data_handler.GetData(integer);
        }

        data_handler.ResetPosition();

        osDelay(50);
    }
}