#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
#include <stdlib.h>
int isVar(char *str);
int isInteger(char *str);
bool isFloat(char *str);
int check_ProperFraction(char *str);
int is_MixedNumber(char *str);

int main()
{
    int n, p, count=0;
    char str[21];
    scanf("%d", &n);//代表有多少次的字串輸入
    //輸入
    for(int i=0; i<n; i++){
        scanf("%s", &str);
        if (isVar(str) == 1){
            printf("variable\n");
        }else if(isInteger(str) == 1){
            printf("integer\n");
        }else if(isFloat(str)){
            int j = 0;
            printf("float\n");//float
            while(str[j] != '.'){//找出小數點位置
                printf("%c", str[j]);//印出小數點前面整數
                j++;
            }
            printf("\n");
            ++j;
            for(j ; j<strlen(str) ; j++){
                printf("%c", str[j]);
            }
            printf("\n");
        }else if(check_ProperFraction(str) == 1){//真分數
            printf("proper fraction\n");
        }else if(is_MixedNumber(str)){
            printf("algebraic fraction\n");
        }else{
            printf("error\n");
        }
    }
}

int isVar(char *str) //變數
{
    int i = 0;
    // 檢查第一個字元是否為英文字母或是'_'
    if (!(isalpha(str[i]) || str[i] == '_')) {
        return 0;
    }
    i++;
    // 檢查每個字元是否都為英文字母、數字或是'_'
    while (str[i] != '\0') {
        if (!(isalnum(str[i]) || str[i] == '_')) {
            return 0;
        }
        i++;
    }
    // 字串符合條件，印出變數
    //printf("%s is a valid identifier.\n", str);
    return 1;
}

int isInteger(char *str)//整數
{
    int i=0,len;
    len=strlen(str);//str len
    if (len==1 && isdigit(str[0])){//長度為1，並為數字
        return 1;
    }
    if (str[0] != '0'){ //str 開頭部為0，其他字元不是數字
        while (str[i] != '\0'){
            if (!isdigit(str[i])){
                return 0;
            }
            i++;
        }
        return 1;
    }
    else if(len!=1 && str[0]=='0'){//長度不為1，但開頭為0
                return 0;
    }
    else{
        return 1;
    }
}

bool isFloat(char *str) //float
{
    int dotCount = 0;
    int zeroCount = 0;
    int numCount = 0;

    // 檢查字串是否為空
    if (*str == '\0') {
        return false;
    }

    // 檢查是否為負數
    if (*str == '-') {
        return false;
    }
    if(str[0]=='.'){//開頭為小數點
        return false;
    }

    // 檢查字串內容
    while (*str != '\0') {
        // 檢查是否為數字
        if (*str >= '0' && *str <= '9') {
            numCount++;
        }
        // 檢查是否為小數點
        else if (*str == '.') {
            dotCount++;
        }
        // 其他情況，非法字元
        else {
            return false;
        }

        // 檢查小數點數量
        if (dotCount > 1) {
            return false;
        }

        // 檢查開頭是否為0
        if (numCount == 1 && *str == '0') {
            zeroCount++;
            // 若開頭為0，最多一個
            if (zeroCount > 1) {
                return false;
            }
        }

        // 移動到下一個字元
        str++;
    }

    // 檢查結尾是否為小數點
    if (*(str - 1) == '.') {
        return false;
    }

    // 若全部檢查完，則為浮點數
    return true;
}

int check_ProperFraction(char *str) //真分數
{
    int numerator = 0, denominator = 0, i = 0;

    while (isspace(str[i])) {
        i++;
    }

    if (!isdigit(str[i]) || str[i] == '0') {
        return 0;
    }

    while (isdigit(str[i])) {
        numerator = numerator * 10 + (str[i] - '0');
        i++;
    }

    if (str[i] != '/') {
        return 0;
    }
    i++;

    if (!isdigit(str[i]) || str[i] == '0') {
        return 0;
    }

    while (isdigit(str[i])) {
        denominator = denominator * 10 + (str[i] - '0');
        i++;
    }

    while (isspace(str[i])) {
        i++;
    }

    if (str[i] != '\0') {
        return 0;
    }

    if (numerator >= denominator) {
        return 0;
    }

    return 1;
}

// 判斷是否為數字
int isNumber(char c) 
{
    return isdigit(c) && c != '0';
}

int is_MixedNumber(char *str) //帶分數
{
    int count = 0;
    for (int i = 0; i < strlen(str); i++) {
        if (str[i] =='/') {
            count++;
        }
    }
    if(count!=1){
        return 0;
    }
    //return count;

    char *left_paren = strchr(str, '(');
    char *right_paren = strchr(str, ')');
    if (left_paren == NULL || right_paren == NULL) {
        return 0;
    }

    char *int_part = strtok(str, "(");
    char *frac_part = strtok(NULL, ")");

    // 檢查整數部分、分子和分母是否都是數字
    for (int i = 0; i < strlen(int_part); i++) {
        if (!isdigit(int_part[i])) {
            return 0;
        }
    }
    char *numerator = strtok(frac_part, "/");
    char *denominator = strtok(NULL, "/");
    if (numerator == NULL || denominator == NULL) {
        return 0;
    }
    for (int i = 0; i < strlen(numerator); i++) {
        if (!isdigit(numerator[i])) {
            return 0;
        }
    }
    for (int i = 0; i < strlen(denominator); i++) {
        if (!isdigit(denominator[i])) {
            return 0;
        }
    }
    for (int i = 0; i < strlen(int_part); i++) {
        if (i == 0 && int_part[i] == '0') {
            return 0;
        }
    }
    for (int i = 0; i < strlen(numerator); i++) {
        if (i == 0 && numerator[i] == '0') {
            return 0;
        }
    }

    int int_part_num = atoi(int_part);
    int numerator_num = atoi(numerator);
    int denominator_num = atoi(denominator);

    // 檢查分數是否正確
    if (numerator_num >= denominator_num || denominator_num == 0) {
        return 0;
    }
    return 1;
}
