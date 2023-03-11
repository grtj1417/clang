#include <stdio.h>
int main()
{
    
    int S0 = 0 , S1_original = 0 , S1 = 0;
    
    scanf("%d \n%d" , &S0 , &S1);
    S1_original = S1;

    //add
    int a = 0 , b = 0 , c = 0;
    scanf("%d %d %d", &a , &b , &c);
    S1 = S1 | (1 << a);
    S1 = S1 | (1 << b);
    S1 = S1 | (1 << c);

    //remove
    int d = 0 , e = 0 , f = 0;
    scanf("%d %d %d", &d , &e , &f);
    S1 = S1 & ~(1 << d);
    S1 = S1 & ~(1 << e);
    S1 = S1 & ~(1 << f);

    if((S1 | S0) == S0){
        printf("Y\n");
    }else{
        printf("N\n");
    }
    printf("%d\n", S1_original & S1);
    printf("%d\n", S1_original | S1);
    return 0;
}