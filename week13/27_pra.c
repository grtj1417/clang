#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define PI 3.14

#define ShapeText(TYPE)\
    char name[10];\
    (*perimeter)(struct TYPE*);\
    (*area)(struct TYPE*);\

typedef struct shape_s{
    ShapeText(shape_s);
}shape_t;

typedef struct circle_s{
    ShapeText(circle_s);
    double radius;
}circle_t;

double CirclePerimeter(circle_t *obj)
{
    return 2 * PI * obj->radius;
}

double CricleArea(circle_t *obj)
{
    return obj->radius * obj->radius * PI;
}

void CricleCreate(circle_t *obj)
{
    strcpy(obj->name, 'C');
    obj->perimeter = CirclePerimeter;
    obj->area = CricleArea;
}

int main()
{
    int N;
    scanf("%d", &N);
    shape_t* shapes[N];
    
    for(int i = 0; i < N; i++){
        char shapeType;
        scanf("%c", &shapeType);
        if(shapeType == 'C'){
            circle_t *circle = (circle_t*)malloc(sizeof(circle_t));
            CricleCreate(circle);
            scanf("%lf", circle->radius);
            shapes[i] = (shape_t*)circle;
        }
    }

    double totalPerimeter = 0, totalArea = 0;
    for(int i = 0; i < N; i++){
        shape_t* shape = shapes[i];
        printf("%lf\n%lf\n", shape->perimeter, shape->area);
        double perimeter = shape->perimeter(shape);

    totalPerimeter += perimeter;
    totalArea += shape->area(shape);
    }
    return 0;
}