#include <stdio.h>

int main() 
{
    char *a[1024];
    for (int i = 0; i < 5; i++) {
        gets(a);
        printf("%c",a);
    }
    return 0;
}
