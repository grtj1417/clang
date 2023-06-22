#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

// 狀態機狀態
enum State {
    Start,
    Var,
    Int,
    Float,
    FloatBody,
    ProperFraction,
    AlgebraicFraction,
    Error
};

// 狀態機轉移函數
enum State transfer(enum State state, char c) {
    int count_point;

    //開頭
    if (state == Start) {
        if (isupper(c) || islower(c) || c == '_') {
            return Var;
        } else if (isdigit(c) ) {
            return Int;
        } else if (c == '.') {
            count_point ++;
            return Float;
        } else {
            return Error;
        }
    //變數
    } else if (state == Var) {
        if (isupper(c) || islower(c) || isdigit(c) || c == '_') {
            return Var;
        } else {
            return Error;
        }
    //整數
    } else if (state == Int) {
        if (isdigit(c)) {
            return Int;
        } else if (c == '/') {
            return ProperFraction;
        } else if (c == '(' || c ==')') {
            return AlgebraicFraction;
        } else if (c == '.') {
            count_point ++;
            if(count_point > 1) return Error;
            return Float;
        } else {
            return Error;
        }
    //浮點數
    } else if (state == Float) {
        if (isdigit(c)) {
            return Float;
        } else if (c == '.') {
            count_point ++;
            if(count_point > 1) return Error;
            return Float;
        } else if (c == '0') {
            return Float;
        } else {
            return Error;
        }
    //真分數
    } else if (state == ProperFraction) {
        if (isdigit(c) || c == '/') {
            return ProperFraction;
        } else if (c == '(' || c == ')' ) {
            return AlgebraicFraction;
        } else {
            return Error;
        }
    //代分數
    } else if (state == AlgebraicFraction) {
        int countAl_sl;
        if (isdigit(c)) {
            return AlgebraicFraction;
        }else if ( c == '/'){
            if(c == '/') countAl_sl += 1;
            if(countAl_sl > 1) return Error; //計算斜線次數
        }else if ( c == '(' || c == ')'){
            return AlgebraicFraction;
        }else {
            return Error;
        }
    } else {
        return Error;
    }
}

enum State checkEnd(enum State state, char str[21]){
    for(int i = 0; i < 21; i++){
        // if(str[i] = '/'){
        //     if(str[i + 1] = '\0') return Error;
        // }
        if(str[i] == '('){
            if(str[i + 1] == ')') return Error;
        }
    }
}

int main() {
    int n = 0;
    int flag = 0;
    char str[21];
    scanf("%d", &n);
    getchar(); // 把換行符號吃掉

    while (n--) {
        fgets(str, sizeof(str), stdin);

        enum State state = Start;
        for (int i = 0; str[i] != '\n' && str[i] != '\0'; i++) {
            state = transfer(state, str[i]);
        }

        if (state == Var) {
            printf("variable\n");
        } else if (state == Int) {
            printf("integer\n");
        } else if (state == Float) {
            double num = atoi(str);
            int decimal = (int) ((num - (int)num) * 100000); // 取得小數點後五位的數字
            if(decimal == 0) printf("error\n");
            printf("float\n");
            char *decimal_point = strchr(str, '.');
            printf("%.*s\n", (int)(decimal_point - str), str);
            printf("%s\n", decimal_point + 1);

        } else if (state == ProperFraction) {
            for(int i = 0; i < 21; i++){
                if(str[i] = '/'){
                    if(str[i + 1] = '\0') printf("error\n");
                }
            }
            printf("proper fraction\n");

        } else if (state == AlgebraicFraction) {
            // checkEnd(state, str);
            // if(state == Error) printf("error");
            printf("algebraic fraction\n");
            // char *AF_denNull_char = strchr(str, '/'); // 從 '/' 拆開
            // char *AF_den_char;
            // AF_den_char = strchr(AF_denNull_char + 1, ')'); // 從 ')' 拆開
            // if (AF_denNull_char+1 == NULL ) { // 分母
            //     printf("error\n");
            // } else {
            //     int AF_den_int = atoi(AF_den_char + 1);  // 分母字串轉整數
            //     int AF_num_int = (int)(AF_den_char - str); // 
            //     // AF_num_int = atoi(AF_den_char - str);  // 分子字串轉整數
            //     if (AF_den_int <= 0) {
            //         printf("error\n");
            //     }else if(AF_num_int > AF_den_int){
            //         printf("error\n");
            //     } else {
            //         printf("algebraic fraction\n");
            //     }
            // }
        } else {
            printf("error\n");
        }
    }

    return 0;
}