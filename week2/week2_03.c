#include <stdio.h>
int main()
{
    int N =2 , M = 0;
    scanf("%d\n %d", &N, &M);
    if(N = 1 && 2 <= M && M <= 9) {
        for (int i = 1; i <= M; i++){
            for(int j = 1; j <= M-i; j++){
                printf("#");
            }
            printf("*");
                for(int j = 1; j <= i-1; j++){
                    char a, b, c, output;
                    a = 'A';
                    b = 'B';
                    c = 'C';
                    switch(i){
                        case 2: case 5: case 8:
                        output = a;
                        break;
                        case 3: case 6: case 9:
                        output = b;
                        break;
                        case 4: case 7: case 10:
                        output = c;
                        break;
                    }
                    printf("%c",output);
                    printf("*");
                }       
            for(int j = 1; j <= M-i; j++){
                printf("#");
            }
        printf("\n");
        }
    }else if (N = 2 && 2 <= M && M <= 9){
        for (int i = 1; i <= M; i++) {
            for (int j = 1; j <= i; j++) {
                printf("%d", j);
            }
            for (int k = 1; k <= ((M-i)*2+2); k++) {
                printf("*");
            }
            for (int j = i; j >= 1; j--) {
                printf("%d", j);
            }
            printf("\n");
        }
    }else if(N !=1 && N !=2) printf("error");
    return 0;
}