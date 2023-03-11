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
    } else if (state == Var) {
        if (isupper(c) || islower(c) || isdigit(c) || c == '_') {
            return Var;
        } else {
            return Error;
        }
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
    } else if (state == Float) {
        if (isdigit(c)) {
            return Float;
        } else if (c == '.') {
            count_point ++;
            if(count_point > 1) return Error;
        } else if (c == '0') {
            return Float;
        } else {
            return Error;
        }
    } else if (state == ProperFraction) {
        if (isdigit(c)) {
            return ProperFraction;
        } else if (c == '(' || c == ')' ) {
            return AlgebraicFraction;
        } else {
            return Error;
        }
    } else if (state == AlgebraicFraction) {
        int countAl_sl;
        if (isdigit(c) || c == '/') {
            if(c == '/') countAl_sl += 1;
            if(countAl_sl > 1) return Error; //計算斜線次數
            return AlgebraicFraction;
        }else if ( c == '(' || c == ')'){
            return AlgebraicFraction;
        }else {
            return Error;
        }
    } else {
        return Error;
    }
}

// enum State checkEnd(enum State state, char e){
//     if (e != '\0' || e != '\n' || e != '_' || e != ')')
//     return Error;
//     // else if (isdigit(e) != 1)
//     // return Error;
// }

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
        // for(int j = 21; str[j] == '\0' || str[j] == '\n'; j--){
        //     state = checkEnd(state, str[j]);
        // }
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
            printf("proper fraction\n");
        } else if (state == AlgebraicFraction) {
            char *AF_denNull_char = strchr(str, '/'); // 從 '/' 拆開
            char *AF_den_char;
            AF_den_char = strchr(AF_denNull_char + 1, ')'); // 從 ')' 拆開
            if (AF_denNull_char+1 == NULL ) { // 分母
                printf("error\n");
            } else {
                int AF_den_int = atoi(AF_den_char + 1);  // 分母字串轉整數
                int AF_num_int = (int)(AF_den_char - str); // 
                // AF_num_int = atoi(AF_den_char - str);  // 分子字串轉整數
                if (AF_den_int <= 0) {
                    printf("error\n");
                }else if(AF_num_int > AF_den_int){
                    printf("error\n");
                } else {
                    printf("algebraic fraction\n");
                }
            }
        } else {
            printf("error\n");
        }
    }

    return 0;
}