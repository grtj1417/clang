#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>

#define PI 3.14

#define ShapeText(TYPE) \
    char name[10]; \
    double (*perimeter)(struct TYPE*); \
    double (*area)(struct TYPE*);

typedef struct shape_s {
    ShapeText(shape_s);
} shape_t;

typedef struct circle_s {
    ShapeText(circle_s);
    double radius;
} circle_t;

typedef struct rect_s {
    ShapeText(rect_s);
    double length, width;
} rect_t;

typedef struct square_s {
    ShapeText(square_s);
    double edge;
} square_t;

typedef struct triangle_s {
    ShapeText(triangle_s);
    double edge1, edge2, edge3;
} triangle_t;

double CirclePerimeter(circle_t* obj) {
    return 2 * PI * obj->radius;
}

double CircleArea(circle_t* obj) {
    return obj->radius * obj->radius * PI;
}

void CircleCreate(circle_t* obj) {
    strcpy(obj->name, "C");
    obj->perimeter = CirclePerimeter;
    obj->area = CircleArea;
}

double RectPerimeter(rect_t* obj) {
    return (obj->length + obj->width) * 2;
}

double RectArea(rect_t* obj) {
    return obj->length * obj->width;
}

void RectCreate(rect_t* obj) {
    strcpy(obj->name, "R");
    obj->perimeter = RectPerimeter;
    obj->area = RectArea;
}

double SquarePerimeter(square_t* obj) {
    return obj->edge * 4;
}

double SquareArea(square_t* obj) {
    return obj->edge * obj->edge;
}

void SquareCreate(square_t* obj) {
    strcpy(obj->name, "S");
    obj->perimeter = SquarePerimeter;
    obj->area = SquareArea;
}

double TrianglePerimeter(triangle_t* obj) {
    return obj->edge1 + obj->edge2 + obj->edge3;
}

double TriangleArea(triangle_t* obj) {
    double s = (obj->edge1 + obj->edge2 + obj->edge3) / 2;
    return sqrt(s * (s - obj->edge1) * (s - obj->edge2) * (s - obj->edge3));
}

void TriangleCreate(triangle_t* obj) {
    strcpy(obj->name, "T");
    obj->perimeter = TrianglePerimeter;
    obj->area = TriangleArea;
}

int main() {
    int N;
    scanf("%d", &N);
    
    shape_t* shapes[N];
    double totalPerimeter = 0;
    double totalArea = 0;

    for (int i = 0; i < N; i++) {
        char shapeType;
        scanf(" %c", &shapeType);

        if (shapeType == 'C') {
            circle_t* circle = (circle_t*)malloc(sizeof(circle_t));
            CircleCreate(circle);
            scanf("%lf", &circle->radius);
            shapes[i] = (shape_t*)circle;
        } else if (shapeType == 'R') {
            rect_t* rect = (rect_t*)malloc(sizeof(rect_t));
            RectCreate(rect);
            scanf("%lf %lf", &rect->length, &rect->width);
            shapes[i] = (shape_t*)rect;
        } else if (shapeType == 'S') {
            square_t* square = (square_t*)malloc(sizeof(square_t));
            SquareCreate(square);
            scanf("%lf", &square->edge);
            shapes[i] = (shape_t*)square;
        } else if (shapeType == 'T') {
            triangle_t* triangle = (triangle_t*)malloc(sizeof(triangle_t));
            TriangleCreate(triangle);
            scanf("%lf %lf %lf", &triangle->edge1, &triangle->edge2, &triangle->edge3);
            shapes[i] = (shape_t*)triangle;
        }
    }

    for (int i = 0; i < N; i++) {
        shape_t* shape = shapes[i];
        double perimeter = shape->perimeter(shape);
        double area = shape->area(shape);
        totalPerimeter += perimeter;
        totalArea += area;
        printf("%.2lf %.2lf\n", perimeter, area);
    }

    printf("%.2lf %.2lf\n", totalPerimeter, totalArea);

    // Free allocated memory
    for (int i = 0; i < N; i++) {
        free(shapes[i]);
    }

    return 0;
}
