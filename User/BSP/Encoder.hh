#pragma once

#include "tim.h"

class Encoder {
private:
    TIM_HandleTypeDef* htim_;

    uint32_t channel_a_;
    uint32_t channel_b_;

    uint8_t carry_ = 0;

public:
    /// @brief 定时器的注册
    /// @param htim 定时器的句柄
    /// @param channel_a A通道
    /// @param channel_b B通道
    Encoder(TIM_HandleTypeDef* htim, uint32_t channel_a, uint32_t channel_b)
        : htim_(htim)
        , channel_a_(channel_a)
        , channel_b_(channel_b)
    {
        HAL_TIM_Encoder_Start(htim_, TIM_CHANNEL_ALL);
    }

    /// @brief 读取当前定时器的计数值
    /// @return 返回当前的计数值
    int ReadCount()
    {
        uint32_t count = __HAL_TIM_GET_COUNTER(htim_);

        if (carry_ == 0)
            return count - htim_->Init.Period / 2;

        return 0;
    }

    /// @brief 清空当前的计数值, 使计数值为上限的一半
    void EmptyCount()
    {
        __HAL_TIM_GET_COUNTER(htim_) = htim_->Init.Period / 2;
    }

    /// @brief 设定当前计数值
    /// @param count 设定的值
    void SetCount(int count)
    {
        __HAL_TIM_GET_COUNTER(htim_) = count;
    }

    void PeriodElapsedCallback(TIM_HandleTypeDef* htim)
    {
        if (htim != htim_)
            return;

        if (__HAL_TIM_GET_COUNTER(htim_) == htim_->Init.Period) {
            carry_++;
        }
        else {
            carry_--;
        }
    }
};
