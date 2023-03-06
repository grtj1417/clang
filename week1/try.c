#include <stdio.h>
int main()
{
    int a , b;
    scanf("%d", &a);
    // b = ((b << a)  | (1 << (a - 1)));
    // b++;
    // b = b << a;
    b = b | (1 << a);
    printf("%d",a);
}