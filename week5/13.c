#include <stdio.h>
#include <math.h>
#include <string.h>

int binary_to_decimal(unsigned char input[13], int *M);

int decimal_to_binary(int num);
void run(unsigned char input[13]);
void run_m_times(int *T, int M);

int cnt(int M)
{
    if(M == 1){
        return 1;
    }else{
        return 1 + cnt((M + 1) / 2);   
    }
}
int main()
{
    unsigned char input[13];
    int M = 0;
    int number = 0;
    scanf("%s", &input);
    while (strcmp(input,"-1"))
    {
        run(input);
        scanf("%s", &input);
    }
    
    return 0;
}


int binary_to_decimal(unsigned char input[11], int *M)
{
    unsigned int j = 0x00000400;
    *M = 0;
    for(int i = 0; i < 10; i++){
        *M = *M + (input[i] - '0') * j;
        j >>= 1;
    }
    return 0;
}

int decimal_to_binary(int num)
{
    int i=13;
    int a[14] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0};
    // printf("%d\n",num);

    while(num != 0){
        a[i] = num % 2;
        num = num / 2;
        i-= 1;
    }
    for(int j = 0; j < 14; j++){
        printf("%d",a[j]);
    }
    // printf("\n");

    return 0;
}

void run(unsigned char input[11])
{
    int M = 0;
    int j = M;
    int number = 0, T = 0;

    

    //二進位轉十進位
    binary_to_decimal(input, &M);
    M /= 2;
    
    if(M == 0){ //輸入為0
        printf("00000000000000\n");
        return;
    }
    // printf("M = %d\n",M);

    while ((M !=1))
    {
        run_m_times(&T, M);
        M -= 1;
        // if(M % 2 == 0){
        //     M /= 2; //原本的M除2後丟下一圈
        // }else if (M % 2 == 1){
        //     M += 1;
        //     M /= 2;
        // }
    }
    // printf("%d\n",T);
    decimal_to_binary(T);
    
    printf("\n");
    return;
}

void run_m_times(int *T, int M)
{
    while(M != 1){
        if(M % 2 == 0){//先做一次?
            M /= 2;
            (*T)++;
        }else if (M % 2 == 1){
            M += 1;
            M /= 2;
            (*T)++;
        }
    }
    // printf("here%d\n",*T);
    return;
}