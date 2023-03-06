#include <stdio.h>
int gcd(int n1, int n2){
    while((n1 !=0) && (n2 !=0)){
        if(n1 > n2)
            n1 = n1 % n2;
        else
            n2 = n2 % n1;
    }
    if(n1 > n2) return n1;
    else return n2;
}
int lcm(int n1, int n2){
    return n1*n2/gcd(n1,n2);
}
int main()
{
    int a, b, c, answer;
    scanf("%d%d%d", &a, &b, &c);
    a = lcm(a, b);
    answer = lcm(a, c);
    printf("%d", answer);
    return 0;
}