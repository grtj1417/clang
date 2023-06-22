#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <stdint.h>

#define init_array(arr)        \
    for (int i = 0; i < 15; i++) \
    {                            \
        arr[i] = INT64_MAX;      \
    }

#define SWAP(a, b) \
    {              \
        int64_t t = a; \
        a = b;     \
        b = t;     \
    }

void run();

void selection_sort(int64_t batter_to_int[15])
{
    for (int i = 0; i < 15; i++)
    {
        int min_index = i;
        for (int j = i + 1; j < 15; j++)
        {
            if (batter_to_int[min_index] > batter_to_int[j])
                min_index = j;
        }
        SWAP(batter_to_int[min_index], batter_to_int[i]);
    }
}

// int getMinIndex1(int d[], int left, int right)
// {
//     int i = 0, minIndex = left;
//     for ((i = left + 1); i < right; i++)
//     {
//         if (d[i] < d[minIndex])
//             minIndex = i;
//     }
//     return minIndex;
// }

// void swap(int arr[], int i, int j, int n)
// {
//     int temp;
//     for (int k = 0; k < n; k++)
//     {
//         temp = arr[k];
//         arr[k] = arr[k];
//         arr[k] = temp;
//     }
// }

int main()
{
    run();
    return 0;
}

void run()
{
    int a = 0;
    char b[40];
    int arr[10];
    int i = 0;

    scanf("%d", &a);
    getchar();
    fgets(b, 40, stdin);
    char *token = strtok(b, " ");

    while (token != NULL)
    {
        arr[i++] = atoi(token);
        token = strtok(NULL, " ");
    }

    int count = 0;
    int output[i][a];
    int temp[20][20];
    int head = 0;
    int tail = a;
    int temp_index = 0;

    int countDop = 0;
    while (1)
    {
        if (tail > i)
        {
            break;
        }

        int checkDup = 0;
        for (int k = head; k < tail; k++)
        {
            for (int l = head; l < tail; l++)
            {
                if (k == l)
                    continue;
                if (arr[k] == arr[l]) // 確認是否為正確分散度
                {
                    checkDup = 1;
                    // countDop--;
                    break;
                }
            }
        }
        if (checkDup) // 跳過列裡面重複的
        {
            head++;
            tail++;
            continue;
        }
        int found = 0;
        for (int j = 0; j < temp_index; j++)
        {
            int match = 1;
            for (int k = 0; k < a; k++)
            {
                if (temp[j][k] != arr[head + k])
                {
                    match = 0;

                    break;
                }
            }
            // 找到重複的列
            if (match)
            {
                found = 1;
                countDop++; // 重複的也要算
                break;
            }
        }
        // 如果某兩列一模一樣 頭尾++ 跳出
        if (found)
        {
            head++;
            tail++;
            // countDop--;
            continue;
        }

        // 檢查完 >> 放入temp
        for (int j = 0; j < a; j++)
        {
            temp[temp_index][j] = arr[head + j];
        }

        temp_index++;
        countDop++;
        head++;
        tail++;
    }

    

    // output1
    printf("%d\n", countDop);

    int64_t sorted[15];
    init_array(sorted);
    // output2
    for(int i = 0; i < temp_index;i++){
        sorted[i] = 0;
    }
    for (i = 0; i < temp_index; i++)
    {
        for (int j = 0, k = a-1; j < a; j++, k--)
        {
            // printf("%d ", temp[i][j]);
            int64_t pow = 1;
            for(int pow_c = k; pow_c > 0; pow_c--){
                pow *= 10;
            }
            sorted[i] += (int64_t)temp[i][j] * pow;
        }
    }

    // int min_index = 0;
    // for(i = 0; i < temp_index; i++){
    //     min_index = getMinIndex1(sorted, i, temp_index);
    //     swap(temp, i, min_index, temp_index);
    // }

    selection_sort(sorted);

    //print sorted


    int64_t pow = 1;
    for(int i = 0; i < a; i++){
        pow *= 10;
    }

    for(i = 0; i < temp_index; i++){
        int64_t temp_pow = pow/10;
        for(int j = 0; j < a; j++){
            int64_t res = sorted[i] / temp_pow; //該位數數字
            sorted[i] -= res * temp_pow; //減掉不必要的輸出
            temp_pow /= 10;
            printf("%lld ", res);
        }
        if(i == temp_index - 1)break;
        printf("\n");
    }
}