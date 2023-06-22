#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define PI 3.14

#define ShapeText(TYPE){
    char name[10];\
    double (*perimeter)(struct TYPE*);\
    double (*area)(struct TYPE*);\
}

typedef struct shape_s{
    ShapeText(shape_s);
}shape_t;

typedef struct circle_s {
    ShapeText(circle_s);
    double radius;
} circle_t;

typedef struct rectangle_s{
    ShapeText(rectangle_s);
    double width, length;
}rectangle_t;

typedef struct square_s{
    ShapeText(square_s);
    double edge;
}square_t;

typedef struct triangle_s{
    ShapeText(triangle_s);
    double edge;
}triangle_t;

//circle
double CirclePerimeter(circle_t* obj) {
    return 2 * PI * obj->radius;
}