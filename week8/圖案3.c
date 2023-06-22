#include <stdio.h>
int main()
{
    int N, M;
    scanf("%d\n%d", &N, &M);
    if(N ==1){
        for(int i = 1; i <= M - 1; i++){
            for(int j = 1; j <= M - i; j++){
                printf("#");
            }

            printf("*");

            for(int j = 1; j <= i - 1; j++){
                if(i == 1) continue;
                int abc_number = i % 3;
                switch(abc_number){
                case 2:
                    printf("A");
                    break;
                case 0:
                    printf("B");
                    break;
                case 1:
                    printf("C");
                    break;
                }
                printf("*");
            }

            for(int j = 1; j <= M - i; j++){
                printf("#");
            }
            printf("\n");
        }
    }

    if(N == 2){
        for(int i = 1; i <= M; i++){
            for(int j = 1; j <= i; j++){
                printf("%d",j);
            }
            for(int k = 0; k < (M-i)*2+2; k++){
                printf("*");
            }
            for(int j = i; j >= 1; j--){
                printf("%d",j);
            }
            printf("\n");
        }
    }
    return 0;
}
