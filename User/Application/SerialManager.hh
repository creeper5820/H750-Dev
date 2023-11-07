#pragma once

#include "dma.h"
#include "usart.h"
#include "cmsis_os.h"

#define CACHE_SIZE 50

typedef enum {
    WAIT,
    READY,
} Status;

class SerialManager
{
private:
    UART_HandleTypeDef *huart_;
    uint8_t status_ = READY;
    uint8_t cache_[CACHE_SIZE];
    uint32_t cache_size_ = 0;

public:
    SerialManager(UART_HandleTypeDef *huart)
        : huart_(huart)
    {
    }

    HAL_StatusTypeDef Send(uint8_t type, uint8_t *data, uint16_t size, uint32_t time_out = 50);
    HAL_StatusTypeDef Recevice(uint8_t type, uint32_t time_out = 50);

    UART_HandleTypeDef *GetHandleType();

    uint8_t GetStatus()
    {
        return status_;
    }

    uint8_t *GetData()
    {
        return cache_;
    }

    uint32_t GetDataSize()
    {
        return cache_size_;
    }

    void SetWait()
    {
        status_ = WAIT;
    }

    void SetReady()
    {
        status_ = READY;
    }

    void SetSize(uint32_t size)
    {
        cache_size_ = size;
    }

    void EmptyCache()
    {
        for (uint32_t i = cache_size_; i < 50; i++) {
            cache_[i] = '\0';
        }
    }

    void HelloWorld(uint8_t type)
    {
        Send(type, (uint8_t *)&"Hello World!\n", sizeof("Hello World!"));
    }
};
