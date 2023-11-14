#pragma once

#include "main.h"
#include "gpio.h"

#define ColorType uint16_t

typedef struct Point {
    int x;
    int y;
} Point;

class Display
{
private:
    int display_width_;
    int display_length_;

    ColorType color_ = 0;
    int Thickness_   = 0;
    bool IsSolid     = 0;

public:
    Display(int display_width, int display_length)
        : display_width_(display_width),
          display_length_(display_length)
    {
    }

    virtual void Init();
    virtual void DrawPoint(Point point);

    void SetColor(ColorType color_);
    void SetThickness(int Thickness);
    void SetSolid(bool IsSolid);

    void DrawMatrix();

    void DrawLine(Point point_1, Point point_2);
    void DrawRectangle(Point point_1, Point point_2);
    void DrawRectangle(Point point, int witch, int length);
    void DrawTriangle(Point point_1, Point point_2, Point point_3);
    void DrawElliptic(Point point, int radius_x, int radius_y);
};