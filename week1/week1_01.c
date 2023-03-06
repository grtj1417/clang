#include <stdio.h>
#include <math.h>

int main()
{
    int a = 0 , b = 0, c = 0;
    scanf("%d \n%d \n%d", &a, &b, &c);
    printf("%.1f\n", ((-b) + sqrt(b * b - 4 * a * c)) / (2 * a));
    printf("%.1f\n", ((-b) - sqrt(b * b - 4 * a * c)) / (2 * a));

    return 0;
} 