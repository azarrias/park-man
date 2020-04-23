#ifndef UTIL_H_
#define UTIL_H_

typedef struct Vector { 
    int x;
    int y;
} Vector;

typedef struct Rect {
    int x;
    int y;
    int w;
    int h;
} Rect;

enum class Orientation { Left, Right, Up, Down };

#endif