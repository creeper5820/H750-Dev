#pragma once

#include "main.h"
#include <memory.h>

#define CACHE_SIZE_DATA 20
#define CHECK_SIZE_FRONT 3
#define CHECK_SIZE_BACK 3

class DataHandler {
private:
    uint8_t cache_[CACHE_SIZE_DATA];
    uint16_t size_ = 0;
    uint16_t position_ = 0;

    uint8_t check_front_[CHECK_SIZE_FRONT];
    uint8_t check_back_[CHECK_SIZE_BACK];

    bool order_ = 1;

public:
    DataHandler()
    {
    }

    /// @brief 将接收到的数据包加载进这个工具类的缓存中
    /// @param data 数据包头指针
    /// @param size 数据包的大小
    void Load(const uint8_t* data, uint16_t size)
    {
        Empty();

        size_ = size;
        memcpy(cache_, data, size * sizeof(uint8_t));
    }

    /// @brief 设置头校验位, 校验位数量由宏定义来决定
    /// @param check 特定位数的数组引用
    void SetCheckFront(const uint8_t(&check)[CHECK_SIZE_FRONT])
    {
        memcpy(check_front_, check, sizeof(check_front_));
    }

    /// @brief 设置尾校验位, 校验位由宏定义来决定
    /// @param check 特定位数的数组引用
    void SetCheckBack(const uint8_t(&check)[CHECK_SIZE_BACK])
    {
        memcpy(check_back_, check, sizeof(check_back_));
    }

    /// @brief 设置数据顺序
    /// @param order 1: 数据位从小到大排列, 0: 数据为从大到小排列
    void SetOrder(const bool order)
    {
        order_ = order;
    }

    /// @brief 清空数据缓存
    void Empty()
    {
        memset(cache_, '\0', sizeof(cache_));
    }

    /// @brief 检测首尾校验位,判断数据包是否合法
    /// @return bool, 合法即传回1
    bool IsVaild()
    {
        if (size_ < 7)
            return 0;

        bool flag = 0;

        for (int count = 0; count < CHECK_SIZE_FRONT; count++) {
            if (cache_[count] != check_front_[count])
                flag = 1;
        }

        for (int count = 0; count < CHECK_SIZE_BACK; count++) {
            if (cache_[size_ - CHECK_SIZE_BACK + count] != check_back_[count])
                flag = 1;
        }

        if (flag == 1)
            return 0;

        return 1;
    }

    template <typename T>
    void GetData(T(&data))
    {
        // 限制不足位数的情况
        if (position_ + 1 + CHECK_SIZE_BACK > size_)
            return;

        // 获取第一位数据时.跳过校验位
        if (position_ == 0)
            position_ += CHECK_SIZE_FRONT;

        // 要获取数据的大小
        int size = sizeof(T) / sizeof(uint8_t);

        data = 0;

        uint8_t* temp = reinterpret_cast<uint8_t*>(&data);

        for (int i = 0; i < size; i++) {
            temp[i] = cache_[position_ + i];
        }

        position_ += size;
    }

    void ResetPosition()
    {
        position_ = 0;
    }

    void
};
