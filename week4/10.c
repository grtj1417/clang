#include <stdio.h>
void run();
char A_B_cal(char *answer, char *guess, int *A, int *B);

int main()
{
    run();
    return 0;
}

void run()
{
    char answer[5], guess[5];
    int A = 0, B = 0, count = 0;
    scanf("%s\n", answer);
    for(int i = 0; i < 7; i++){
        scanf("%s", guess);
        count++;
        A_B_cal(answer, guess, &A, &B);
        if(count == 6 && A != 4){
            printf("%dA%dB\n", A, B);
            break;
        }
        if(A == 4){
            printf("win");
            return;
        }else printf("%dA%dB\n", A, B);
        A = 0; B = 0;
    }
    printf("loss");
    return;
}

char A_B_cal(char *answer, char *guess, int *A, int *B)
{
    for(int i = 0; i < 4; i++){
        for(int j = 0; j < 4; j++){
            if(answer[i] == guess[j])
            (*B)++;
        }
    }
    for(int i = 0; i < 4; i++){
        if(answer[i] == guess[i]){
            (*A)++;
            (*B)--;
        }
    }
    return 0;
}