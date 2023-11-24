#pragma once

#include "dma.h"
#include "usart.h"
#include "cmsis_os.h"
#include "memory.h"

#define CACHE_SIZE 50

typedef enum {
    WAIT,
    READY,
} Status;

class SerialManager {
private:
    UART_HandleTypeDef* huart_;
    uint8_t status_ = READY;
    uint8_t cache_[CACHE_SIZE];
    uint32_t cache_size_ = 0;

public:
    SerialManager(UART_HandleTypeDef* huart);

    HAL_StatusTypeDef Send(uint8_t type, uint8_t* data, uint16_t size, uint32_t time_out = 50);
    HAL_StatusTypeDef Recevice(uint8_t type, uint32_t time_out = 50);

    UART_HandleTypeDef* GetHandleType();
    uint8_t GetStatus();
    uint8_t* GetData();
    uint32_t GetDataSize();

    void SetWait();
    void SetReady();
    void SetSize(uint32_t size);

    void EmptyCache();

    void HelloWorld(uint8_t type);
};
