#pragma once

#include "PidController.hh"
#include "main.h"
#include "gpio.h"
#include "tim.h"

class MotorController {
private:
    PidController pid_;

public:
    MotorController()
    {
    }
};
