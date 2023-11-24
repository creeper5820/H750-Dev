#pragma once

#include "Encoder.hh"

class SpeedMeasure {
private:
    Encoder encoder_;

public:
    SpeedMeasure(TIM_HandleTypeDef* htim, uint32_t channel_a, uint32_t channel_b)
        : encoder_(htim, channel_a, channel_b)
    {
    }
};