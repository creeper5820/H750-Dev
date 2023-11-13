#pragma once

#include "spi.h"
#include "gpio.h"
#include "main.h"
#include "tim.h"

/// 颜色的定义
#define COLOR565(r, g, b) \
    (((r & 0xF8) << 8) |  \
     ((g & 0xFC) << 3) |  \
     ((b & 0xF8) >> 3))

#define Delay(X) osDelay(X)

class Display
{
private:
    // 片选引脚
    GPIO_TypeDef *cs_port_;
    uint16_t cs_;

    // 指令数据选择引脚
    GPIO_TypeDef *dc_port_;
    uint16_t dc_;

    // 背光调整pwm输出引脚
    TIM_HandleTypeDef *tim_;
    uint32_t channel_;

    // spi句柄
    SPI_HandleTypeDef *spi_;

public:
    Display(){};

    void CsOn()
    {
        HAL_GPIO_WritePin(cs_port_, cs_, GPIO_PIN_RESET);
    }

    void CsOff()
    {
        HAL_GPIO_WritePin(cs_port_, cs_, GPIO_PIN_SET);
    }

    void Command(uint8_t command)
    {
        HAL_GPIO_WritePin(dc_port_, dc_, GPIO_PIN_RESET);
        CsOn();
        HAL_SPI_Transmit_DMA(spi_, &command, 1);
        CsOff();
    }

    void Data(uint8_t data)
    {
        HAL_GPIO_WritePin(dc_port_, dc_, GPIO_PIN_SET);
        CsOn();
        HAL_SPI_Transmit_DMA(spi_, &data, 1);
        CsOff();
    }

    /**********************************************
     * 初始化函数
     */

    void InitCs(GPIO_TypeDef *cs_port, uint16_t cs)
    {
        cs_port_ = cs_port;
        cs_      = cs;
    }

    void InitRs(GPIO_TypeDef *dc_port, uint16_t dc)
    {
        dc_port_ = dc_port;
        dc_      = dc;
    }

    void InitTim(TIM_HandleTypeDef *tim, uint32_t channel)
    {
        tim_     = tim;
        channel_ = channel;

        HAL_TIMEx_PWMN_Start(tim_, channel_);
    };

    void InitSpi(SPI_HandleTypeDef *spi)
    {
        spi_ = spi;
    }

    void Init(void)
    {
        SetBrightness(0);

        HAL_GPIO_WritePin(dc_port_, dc_, GPIO_PIN_RESET);
        Delay(120);
        Command(0x11);
        Delay(120);

        // ST7735R Frame Rate
        Command(0xB1);
        Data(0x01);
        Data(0x2C);
        Data(0x2D);

        Command(0xB2);
        Data(0x01);
        Data(0x2C);
        Data(0x2D);

        Command(0xB3);
        Data(0x01);
        Data(0x2C);
        Data(0x2D);
        Data(0x01);
        Data(0x2C);
        Data(0x2D);

        Command(0xB4); // Column inversion
        Data(0x07);

        // ST7735R Power Sequence
        Command(0xC0);
        Data(0xA2);
        Data(0x02);
        Data(0x84);
        Command(0xC1);
        Data(0xC5);

        Command(0xC2);
        Data(0x0A);
        Data(0x00);

        Command(0xC3);
        Data(0x8A);
        Data(0x2A);
        Command(0xC4);
        Data(0x8A);
        Data(0xEE);

        Command(0xC5); // VCOM
        Data(0x0E);

        Command(0x36); // MX, MY, RGB mode
        Data(0xC0);

        // Command(0x0A);
        // Data(0);
        // Data(1);
        // Data(0);
        // Data(160);

        // Command(0x0B);
        // Data(0);
        // Data(1);
        // Data(0);
        // Data(80);

        // ST7735R Gamma Sequence
        Command(0xe0);
        Data(0x0f);
        Data(0x1a);
        Data(0x0f);
        Data(0x18);
        Data(0x2f);
        Data(0x28);
        Data(0x20);
        Data(0x22);
        Data(0x1f);
        Data(0x1b);
        Data(0x23);
        Data(0x37);
        Data(0x00);
        Data(0x07);
        Data(0x02);
        Data(0x10);

        Command(0xe1);
        Data(0x0f);
        Data(0x1b);
        Data(0x0f);
        Data(0x17);
        Data(0x33);
        Data(0x2c);
        Data(0x29);
        Data(0x2e);
        Data(0x30);
        Data(0x30);
        Data(0x39);
        Data(0x3f);
        Data(0x00);
        Data(0x07);
        Data(0x03);
        Data(0x10);

        Command(0x2a);
        Data(0x00);
        Data(0x00);
        Data(0x00);
        Data(0x7f);

        Command(0x2b);
        Data(0x00);
        Data(0x00);
        Data(0x00);
        Data(0x9f);

        Command(0xF0); // Enable test command
        Data(0x01);
        Command(0xF6); // Disable ram power save mode
        Data(0x00);

        Command(0x3A); // 65k mode
        Data(0x05);

        Command(0x29); // Display on
    }

    void SetBrightness(float brightness)
    {
        __HAL_TIM_SetCompare(tim_, channel_, (1 - brightness) * htim1.Init.Period);
    }
};