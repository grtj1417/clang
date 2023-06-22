#include <stdio.h>
int ack(int m, int n)
{
    // printf("1 ");
    if(m == 0)
        return n + 1;
    else if(m > 0 && n == 0)
        return ack(m - 1, 1);
    else if(m > 0 && n > 0)
        return ack(m-1, ack(m, n - 1));
}
int main()
{
    int MAX = 1000000;
    for(int i = 0; i < MAX; ++i) {
        for(int j = i; j < MAX; ++j) {
            for(int k = i; k < j; ++k) {
                printf("%d %d %d\n", i, j, k);
            }
        }
    }
    return 0;
}