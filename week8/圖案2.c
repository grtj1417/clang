#include <stdio.h>
int main()
{
    int N, M;
    scanf("%d\n", &N, &M);
    if(N == 1){
        for(int outter = 0; outter < M; outter++){
            for(int i = 0; i < M - 1; i++){
                printf("#");
            }

            printf("*");

            //print ABC
            for(int i = 0; i <= M; i++){
                if(i == 0){
                    continue;
                }else {
                    for(int j = i % 3;j <= M; j++){
                        if(i % 3 == 1){
                            printf("A");
                        }else if(i % 3 == 2){
                            printf("B");
                        }else printf("C");

                        printf("*");
                    }
                }
            for(int i = 0; i < M - 1; i++){
                printf("#");
            }
        }
    }

    if(N == 2){
        for(int i = 1; i <= M; i++){
            for(int j = i+1; j < i; j++){
                printf("%d", j);
            }
            for(int k = 0; k < M*2; k++){
                printf("*");
            }
            for(int j = i; j > i+1; j--){
                printf("%d", j);
            }
        }
    }
    return 0;
}
}
