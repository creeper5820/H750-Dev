#include "SerialManager.hh"

/**
 * @brief 串口发送
 * @param type 模式 0为正常发送 1为DMA发送
 * @param data 数据包的首地址
 * @param size 数据包的大小
 * @param time_out 正常发送的超时时间 默认50ms DMA发送时可以忽略
 * @retval HAL status: HAL_OK(0x00) | HAL_ERROR | HAL_BUSY | HAL_TIMEOUT
 */
HAL_StatusTypeDef SerialManager::Send(uint8_t type, uint8_t *data, uint16_t size, uint32_t time_out = 50)
{
    switch (type) {
        case 0:
            return HAL_UART_Transmit(huart_, (uint8_t *)data, size, time_out);
        case 1:
            return HAL_UART_Transmit_DMA(huart_, (uint8_t *)data, size);
        default:
            break;
    }
}

/**
 * @brief 开启串口接收
 * @param type 0.阻塞接收  1.中断接收  2.DMA  3.ToIdle_DMA
 * @param time_out 阻塞发送的超时时间，默认为50
 * @retval HAL status: HAL_OK(0x00) | HAL_ERROR | HAL_BUSY | HAL_TIMEOUT
 */
HAL_StatusTypeDef SerialManager::Recevice(uint8_t type, uint32_t time_out = 50)
{
    switch (type) {
        case 0:
            return HAL_UART_Receive(huart_, (uint8_t *)cache_, CACHE_SIZE, time_out);
        case 1:
            return HAL_UART_Receive_IT(huart_, (uint8_t *)cache_, CACHE_SIZE);
        case 2:
            return HAL_UART_Receive_DMA(huart_, (uint8_t *)cache_, CACHE_SIZE);
        case 3:
            return HAL_UARTEx_ReceiveToIdle_DMA(huart_, (uint8_t *)cache_, CACHE_SIZE);
        default:
            break;
    }
}

/**
 * @brief 获取串口的操作柄
 * @retval UART_HandleTypeDef
 */
UART_HandleTypeDef *SerialManager::GetHandleType()
{
    return huart_;
}

uint8_t SerialManager::GetStatus()
{
    return status_;
}

uint8_t *SerialManager::GetData()
{
    return cache_;
}

uint32_t SerialManager::GetDataSize()
{
    return cache_size_;
}

void SerialManager::SetWait()
{
    status_ = WAIT;
}

void SerialManager::SetReady()
{
    status_ = READY;
}

void SerialManager::SetSize(uint32_t size)
{
    cache_size_ = size;
}

void SerialManager::EmptyCache()
{
    for (uint32_t i = cache_size_; i < 50; i++) {
        cache_[i] = '\0';
    }
}

void SerialManager::HelloWorld(uint8_t type)
{
    Send(type, (uint8_t *)&"Hello World!\n", sizeof("Hello World!"));
}