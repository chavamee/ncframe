#ifndef NCF_GEOMETRY_H
#define NCF_GEOMETRY_H

struct Point
{
    int x = 0;
    int y = 0;
};

struct Size
{
    int height = 0;
    int width  = 0;
};

struct Rect
{
    Point origin;
    Size  size;
};

#endif
