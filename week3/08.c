#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

void fun();
bool check_with_score(char *input);
void normalize(char *input, char **score, char **upper, char **lower);
void add(int upper_a, int upper_b, int lower_a, int lower_b);
void mul(int upper_a, int upper_b, int lower_a, int lower_b);
int GCD(int t, int v);

int main()
{
    fun();
    char __continue__ = 'y';
    while(scanf(" %c", &__continue__)) {
        if(__continue__ == 'n')
            break;
        fun();
    }
    return 0;
}

void fun()
{
    char input_a[20];
    char input_b[20];
    char cal_sign[10];

    scanf("%s\n%s\n %c", input_a, input_b, cal_sign);

    //a
    char *temp_score_a = (char*) malloc (10*sizeof(char)), *temp_upper_a = (char*) malloc (10*sizeof(char)), *temp_lower_a = (char*) malloc (10*sizeof(char));
    normalize(input_a, &temp_score_a, &temp_upper_a, &temp_lower_a);

    //char轉int
    int score_a, upper_a, lower_a;
    score_a = atoi((const char *)temp_score_a);
    upper_a = atoi((const char *)temp_upper_a);
    lower_a = atoi((const char *)temp_lower_a);

    

    // printf("score = %d,up = %d,low = %d\n",score_a, upper_a, lower_a);
    // 帶分數化假分數
    if(input_a){
        if(score_a > 0){
            upper_a = score_a * lower_a + upper_a;
        }else if(score_a < 0)
            upper_a = score_a * (lower_a) - upper_a;
    }
    // printf("here\n");


    // b
    char *temp_score_b = (char*) malloc (10*sizeof(char)), *temp_upper_b = (char*) malloc (10*sizeof(char)), *temp_lower_b = (char*) malloc (10*sizeof(char));
    normalize(input_b, &temp_score_b, &temp_upper_b, &temp_lower_b);

    //char轉int
    int score_b, upper_b, lower_b;
    score_b = atoi((const char *)temp_score_b);
    upper_b = atoi((const char *)temp_upper_b);
    lower_b = atoi((const char *)temp_lower_b);

    //分母為0
    if(lower_a == 0 || lower_b == 0){
        cal_sign[0] = 'x';
    }
    // 帶分數化假分數
    if(input_b){
        if(score_b > 0){
            upper_b = score_b * (lower_b) + upper_b;
        }else if(score_b < 0)
            upper_b = score_b * (lower_b) - upper_b;
    }
    // printf("imhere3\n");

    //加減乘除
    switch (cal_sign[0]){
    case '+':
        add(upper_a, upper_b, lower_a, lower_b);
        break;
    case '-':
        add(upper_a, -1 * upper_b, lower_a, lower_b);
        break;
    case '*':
        mul(upper_a, upper_b, lower_a, lower_b);
        break;
    case '/':
        if(upper_b < 0 || upper_a < 0)
            mul(upper_a, -1 * lower_b, lower_a, -1 * upper_b);
        else
            mul(upper_a, lower_b, lower_a, upper_b);
        break;
    default:
        printf("error\n");
        break;
    }

}

// 檢驗是否帶分數
bool check_with_score(char *input)
{
    for (char *temp = input; *temp != '\0'; temp++){
        if (*temp == '(')
            return true;
    }
    return false;
}


// 分割
void normalize(char *input, char **score, char **upper, char **lower)
{
    char *val = (char *)malloc(sizeof(char)*20);
    strcpy(val,input);
    if (check_with_score(input)){
        char *p;
        p = strtok(val, "(");
        *score = p;
        p = strtok(NULL, "/");
        *upper = p;
        p = strtok(NULL, ")");
        *lower = p;
    }else{
        char *p;
        p = strtok(val, "/");
        *upper = p;
        p = strtok(NULL, "\0");
        *lower = p;
    }

}

void add(int upper_a, int upper_b, int lower_a, int lower_b)
{
    int temp_up, temp_low, score;
    temp_up = upper_a * lower_b + upper_b * lower_a;
    temp_low = lower_a * lower_b;
    // printf("up = %d,low = %d\n", temp_up, temp_low);
    // 化簡
    int gcd = abs(GCD(temp_up, temp_low));
    temp_up /= gcd; temp_low /= gcd;

    if(temp_low == 1) {
        // if they can be divided
        printf("%d\n", temp_up);
        return;
    }
    int val = temp_up / temp_low;
    if(val != 0) {
        score = temp_up / temp_low;
        temp_up -= score * temp_low;
        printf("%d(%d/%d)\n", score, abs(temp_up), temp_low);
    } else {
        printf("%d/%d\n", temp_up, temp_low);
    }
}

void mul(int upper_a, int upper_b, int lower_a, int lower_b)
{
    int temp_up, temp_low, score;
    temp_up = upper_a * upper_b;
    temp_low = lower_a * lower_b;

    int gcd = abs(GCD(temp_up, temp_low));
    temp_up /= gcd; temp_low /= gcd;

    if(temp_low == 1) {
        // if they can be divided
        printf("%d\n", temp_up);
        return;
    }
    int val = temp_up / temp_low;
    if(val != 0) {
        score = temp_up / temp_low;
        temp_up -= score * temp_low;
        printf("%d(%d/%d)\n", score, abs(temp_up), abs(temp_low));
    } else {
        printf("%d/%d\n", temp_up, abs(temp_low));
    }
    return;
}

int GCD(int t, int v)
{
    if (t % v == 0){
        return v;
    }else{
        return GCD(v, t % v);
    }
}