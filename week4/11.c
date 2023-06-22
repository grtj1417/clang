#include <stdio.h>
#include <math.h>
#include <string.h>

int binary_to_decimal(unsigned char input[13], int *M);
int recursion(int M);
int decimal_to_binary(int num);
void run(unsigned char input[13]);
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

int recursion(int M)
{
    int temp[15][5];
    int i = 0;
    if(M == 1){
        printf("%d ", M);
        temp[i][5] = M;
        i++;
        return 1;
    }else{
        printf("%d ", M);
        temp[i][5] = M;
        i++;
        return 1 + recursion((M + 1) / 2);   
    }

    for(int j = 0; j < 15; j++){
        printf("%d",temp[j][5]);
    }
}

int binary_to_decimal(unsigned char input[13], int *M)
{
    unsigned int j = 0x00000800;
    *M = 0;
    for(int i = 0; i < 12; i++){
        *M = *M + (input[i] - '0') * j;
        j >>= 1;
    }
    return 0;
}

int decimal_to_binary(int num)
{
    int i=3;
    int a[4] = {0,0,0,0};

    while(num != 0){
        a[i] = num % 2;
        num = num / 2;
        i-= 1;
    }
    for(int j = 0; j < 4; j++){
        printf("%d",a[j]);
    }
    printf("\n");

    return 0;
}

void run(unsigned char input[13])
{
    int M = 0;
    int number = 0;

    

    //二進位轉十進位
    binary_to_decimal(input, &M);
    
    if(M == 0){ //輸入為0
        printf("0000\nNo Feedback\n");
        return;
    }else if(M % 2 == 0){//先做一次?
        M /= 2;
    }else if (M % 2 == 1){
        M += 1;
        M /= 2;
    }
    
    decimal_to_binary(cnt(M));
    number = recursion(M);
    printf("\n");
    // printf("\n%d\n", number);    
    // scanf("%s", &input);
}