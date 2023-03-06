#include <stdio.h>
int main()
{
    float w = 0 ,h = 0, b = 0 ;
    scanf("%f \n %f", &w, &h);
    b =  (w / (0.0001 * h * h ) );
    printf("%.1f\n", b);
    return 0;
}