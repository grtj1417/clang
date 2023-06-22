#include <stdio.h>
int main()
{
    int N =2 , M = 0;
    scanf("%d\n %d", &N, &M);
    if(N == 1 && 2 <= M && M <= 9) {
        for (int i = 1; i <= M; i++){
            for(int j = 1; j <= M-i; j++){
                printf("#");
            }
            printf("*");
                for(int j = 1; j <= i-1; j++){
                    switch(i){
                        case 2: case 5: case 8:
                        printf("A");
                        break;
                        case 3: case 6: case 9:
                        printf("B");
                        break;
                        case 4: case 7: case 10:
                        printf("C");
                        break;
                    }
                    printf("*");
                }       
            for(int j = 1; j <= M-i; j++){
                printf("#");
            }
        printf("\n");
        }
    }else if (N == 2 && 2 <= M && M <= 9){
        for (int i = 1; i <= M; i++) {
            for (int j = 1; j <= i; j++) {
                printf("%d", j);
            }
            for (int k = 0; k < ((M-i)*2+2); k++) {
                printf("*");
            }
            for (int j = i; j >= 1; j--) {
                printf("%d", j);
            }
            printf("\n");
        }
    }else printf("error");
    return 0;
}