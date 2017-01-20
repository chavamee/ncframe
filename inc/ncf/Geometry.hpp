#ifndef NCF_NCURSES_GEOMETRY_H_
#define NCF_NCURSES_GEOMETRY_H_

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
