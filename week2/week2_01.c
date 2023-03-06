// #include <stdio.h>
// int checkVariableHead(char input)
//     {
//         int state =0; //START
//         char v1 = 0, v2 = 0;
//         if(input >='a' && input <='z'|| input >='A' && input <='Z' || input == '_')
//             break; //VB
//         else printf("error");
//         if()
//     }

// int main()
// {
//     char input;
//     scanf("%c", &input);
//     printf("%c", checkVariableHead(input));
//     return 0;
// }

#include <stdio.h>
#include <ctype.h>
#include <string.h>

// 狀態機狀態
enum State {
    Start,
    Var,
    Int,
    Float,
    ProperFrac,
    AlgebraicFrac,
    Error
};

// 狀態機轉移函數
enum State transfer(enum State state, char c) {
    if (state == Start) {
        if (isupper(c) || islower(c) || c == '_') {
            return Var;
        } else if (isdigit(c) && c != '0') {
            return Int;
        } else if (c == '.') {
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
            return ProperFrac;
        } else if (c == '.') {
            return Float;
        } else {
            return Error;
        }
    } else if (state == Float) {
        if (isdigit(c)) {
            return Float;
        } else {
            return Error;
        }
    } else if (state == ProperFrac) {
        if (isdigit(c)) {
            return ProperFrac;
        } else if (c == ')') {
            return AlgebraicFrac;
        } else {
            return Error;
        }
    } else if (state == AlgebraicFrac) {
        if (isdigit(c)) {
            return AlgebraicFrac;
        } else {
            return Error;
        }
    } else {
        return Error;
    }
}

int main() {
    int n = 0;
    char str[21];

    scanf("%d", &n);
    // scanf(" %s", &str);
    getchar(); // 把換行符號吃掉

    while (n--) {
        fgets(str, sizeof(str), stdin);

        enum State state = Start;
        int i;
        for (i = 0; str[i] != '\n' && str[i] != '\0'; i++) {
            state = transfer(state, str[i]);
        }

        if (state == Var) {
            printf("variable\n");
        } else if (state == Int) {
            printf("integer\n");
        } else if (state == Float) {
            printf("float\n");
            char *decimal_point = strchr(str, '.');
            printf("%.*s\n", (int)(decimal_point - str), str);
            printf("%s\n", decimal_point + 1);
        } else if (state == ProperFrac) {
            printf("proper fraction\n");
        } else if (state == AlgebraicFrac) {
            printf("algebraic fraction\n");
        } else {
            printf("error\n");
        }
    }

    return 0;
}
