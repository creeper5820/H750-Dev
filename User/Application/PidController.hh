#pragma once

class PidController {
private:
    float kp_ = 0;
    float ki_ = 0;
    float kd_ = 0;

    float value_target_ = 0;

    float bias_ = 0;
    float bias_last_ = 0;
    float bias_last_last_ = 0;
    float bias_integral_ = 0;

    float output_ = 0;
    float output_last_ = 0;
    float output_limit_ = 0;

public:
    PidController()
    {
    }

    PidController(float kp, float ki, float kd)
        : kp_(kp)
        , ki_(ki)
        , kd_(kd)
    {
    }

    void Limit(float* ptr_factor, float limit)
    {
        if (*ptr_factor > limit)
            *ptr_factor = limit;

        if (*ptr_factor < -limit)
            *ptr_factor = -limit;
    }

    void SetKp(float kp)
    {
        kp_ = kp;
    }

    void SetKi(float ki)
    {
        ki_ = ki;
    }

    void SetKd(float kd)
    {
        kd_ = kd;
    }

    void SetTarget(float value_target)
    {
        value_target_ = value_target;
    }

    void SetLimit(float output_limit)
    {
        output_limit_ = output_limit;
    }

    float PositionalControl(float value_actual)
    {
        bias_ = value_target_ - value_actual;
        bias_integral_ += bias_;

        output_
            = kp_ * bias_
            + ki_ * bias_integral_
            + kd_ * (bias_ - bias_last_);

        bias_last_ = bias_;
        output_last_ = output_;

        return output_;
    }

    float IncrementalControl(float value_actual)
    {
        bias_ = value_target_ - value_actual;

        float output_incement
            = kp_ * (bias_ - bias_last_)
            + ki_ * bias_
            + kd_ * (bias_ - 2 * bias_last_ + bias_last_last_);

        bias_last_ = bias_;
        bias_last_last_ = bias_last_;

        output_ += output_incement;
        output_last_ = output_;

        Limit(&output_, output_limit_);

        return output_;
    }
};
