#include "main.h"
#include "cmsis_os.h"
#include "stdio.h"

#include "Encoder.hh"
#include "SerialManager.hh"
#include "SpeedMeasure.hh"

extern "C" {
void EncoderALoop();
void EncoderBLoop();
void EncoderCLoop();
void EncoderDLoop();
}

static int count_a = 0;
static int count_b = 0;
static int count_c = 0;
static int count_d = 0;

void EncoderALoop()
{
    auto encoder_a = Encoder(&htim2, TIM_CHANNEL_1, TIM_CHANNEL_2);

    HAL_TIM_Encoder_Start(&htim2, TIM_CHANNEL_ALL);

    while (1) {
        encoder_a.EmptyCount();
        osDelay(50);
        count_a = encoder_a.ReadCount();
    }
}

void EncoderBLoop()
{
    auto encoder_b = Encoder(&htim4, TIM_CHANNEL_1, TIM_CHANNEL_2);

    HAL_TIM_Encoder_Start(&htim3, TIM_CHANNEL_ALL);

    while (1) {
        encoder_b.EmptyCount();
        osDelay(50);
        count_b = encoder_b.ReadCount();
    }
}

void EncoderCLoop()
{
    auto encoder_c = Encoder(&htim3, TIM_CHANNEL_1, TIM_CHANNEL_2);

    HAL_TIM_Encoder_Start(&htim4, TIM_CHANNEL_ALL);

    while (1) {
        encoder_c.EmptyCount();
        osDelay(50);
        count_c = encoder_c.ReadCount() * 500 / 13;
    }
}

void EncoderDLoop()
{
    auto encoder_d = Encoder(&htim5, TIM_CHANNEL_1, TIM_CHANNEL_2);

    HAL_TIM_Encoder_Start(&htim5, TIM_CHANNEL_ALL);

    while (1) {
        encoder_d.EmptyCount();
        osDelay(50);
        count_d = encoder_d.ReadCount() * 500 / 13;
    }
}