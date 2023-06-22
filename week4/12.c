#include <stdio.h>
#include <string.h>
#define M 100

void sub()
{
    char str_a[M], str_b[M]; // 字元陣列的初始化
    int num_a[M] = {0};      // 被減數陣列
    int num_b[M] = {0};      // 減數陣列
    int num_c[M];            // 差值陣列
    int len_a, len_b;        // 被減數位數，減數位數
    int i, j, k, n, f = 0;

    scanf("%s %s", str_a, str_b);

    len_a = strlen(str_a);
    len_b = strlen(str_b);

    // K的值是參與運算的資料最大位數
    if (len_a > len_b)
        k = len_a;
    else
        k = len_b;
    num_c[0] = 0;

    // n>0表示a>b, n<0表示a<b, n=0表示a=b
    if (len_a > len_b)
        n = 1;
    else if (len_a == len_b)
        n = strcmp(str_a, str_b);
    else
        n = -1;

    // 字元陣列倒序後位數對齊存在整數陣列中
    for (i = len_a - 1, j = 0; i >= 0; i--, j++){
        num_a[j] = str_a[i] - '0';
    }
    for (i = len_b - 1, j = 0; i >= 0; i--, j++){
        num_b[j] = str_b[i] - '0';
    }

    // 具體執行減法運算
    for (i = 0; i < k; i++){
        if (n >= 0){
            if (num_a[i] - num_b[i] >= 0)
                num_c[i] = num_a[i] - num_b[i];
            else{
                num_c[i] = num_a[i] + 10 - num_b[i];
                num_a[i + 1]--;
            }
        }else{
            if (num_b[i] - num_a[i] >= 0)
                num_c[i] = num_b[i] - num_a[i];
            else{
                num_c[i] = num_b[i] + 10 - num_a[i];
                num_b[i + 1]--;
            }
        }
    }

    // 最終結果的輸出
    if (n < 0)
        printf("-");
    for (i = k - 1; i >= 0; i--){
        if (num_c[i])
            f = 1;
        if (f || i == 0)
            printf("%d", num_c[i]);
    }
    printf("\n");
}

void mul()
{
    int a[100], b[100];
    int ans[200] = {0};
    int i, j, tmp;
    char s1[101], s2[101];
    scanf(" %s", s1);
    scanf(" %s", s2);
    int l1 = strlen(s1);
    int l2 = strlen(s2);
    for (i = l1 - 1, j = 0; i >= 0; i--, j++){
        a[j] = s1[i] - '0';
    }
    for (i = l2 - 1, j = 0; i >= 0; i--, j++){
        b[j] = s2[i] - '0';
    }
    for (i = 0; i < l2; i++){
        for (j = 0; j < l1; j++){
            ans[i + j] += b[i] * a[j];
        }
    }
    for (i = 0; i < l1 + l2; i++){
        tmp = ans[i] / 10;
        ans[i] = ans[i] % 10;
        ans[i + 1] = ans[i + 1] + tmp;
    }
    for (i = l1 + l2; i >= 0; i--){
        if (ans[i] > 0)
            break;
    }
    for (; i >= 0; i--){
        printf("%d", ans[i]);
    }
}

int main()
{
    char s_m[40]; // trans to int
    char s_n[40]; // trans to int
    char op;
    int m[M] = {0}; // 數字陣列m
    int n[M] = {0}; // 數字陣列n
    int i, j, len_s_m, len_s_n;
    scanf("%c", &op);

    switch (op){
        case '+':
            scanf("%s", s_m);
            scanf("%s", s_n);

            len_s_m = strlen(s_m);
            len_s_n = strlen(s_n);

            for (i = len_s_m - 1, j = 0; i >= 0; i--){ // 將字元陣列轉化為數字陣列，並倒數存放，作為第一個加數
                m[j] = s_m[i] - '0';
                j++;
            }

            for (i = len_s_n - 1, j = 0; i >= 0; i--){
                n[j] = s_n[i] - '0';
                j++;
            }
            for (i = 0; i <= M; i++){
                m[i] = m[i] + n[i];
                if (m[i] > 9){ // 要進位
                    m[i] = m[i] - 10;
                    m[i + 1]++;
                }
            }
            for (i = M - 1; i >= 0 && m[i] == 0; i--); // 求得最終結果的位數
            if (i > 0){
                for (; i >= 0; i--){ // 最終答案的輸出
                    printf("%d", m[i]);
                }
            }else
                printf("0");
            break;
        case '-':
            sub();
            break;
        case '*':
            mul();
            break;
    }
}
