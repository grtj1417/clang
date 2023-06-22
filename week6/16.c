#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

#define print(x) \
    printf("%d %d %d\n", (x >> 1) & 1, (x >> 2) & 1, (x >> 3) & 1);

#define init_board(board)        \
    for (int i = 0; i < 25; i++) \
    {                            \
        board[i][0] = '\0';      \
        board[i][1] = '\0';      \
    }

#define SWAP(a, b) \
    {              \
        int t = a; \
        a = b;     \
        b = t;     \
    }

int read_input(char board[65][2], char input[1024], unsigned int *outter_count, int batter);
int game(char board[65][2], uint64_t *b, unsigned int *outter_count, int batter_situ[10][3]);



void selectionSort(int batter_to_int[10])
{
    for (int i = 1; i < 10; i++)
    {
        int min_index = i;
        for (int j = i + 1; j < 10; j++)
        {
            if (batter_to_int[min_index] < batter_to_int[j])
                min_index = j;
        }
        SWAP(batter_to_int[min_index], batter_to_int[i]);
    }
}

void first_index_sort(int batter_to_int[10])
{
    for (int i = 1; i < 10; i++)
    {
        int min_index = i;
        for (int j = i + 1; j < 10; j++)
        {
            int index_a_1 = (batter_to_int[min_index])%10;
            int index_b_1 = (batter_to_int[j])%10;
            int index_a_2 = (batter_to_int[min_index]/10)%10;
            int index_b_2 = (batter_to_int[j]/10)%10;
            int index_a_3 = (batter_to_int[min_index]/100)%10;
            int index_b_3 = (batter_to_int[j]/100)%10;

            if (index_a_2 == index_b_2 && index_a_3 == index_b_3 && index_a_1 > index_b_1)
                min_index = j;
        }
        SWAP(batter_to_int[min_index], batter_to_int[i]);
    }
}



int calculat_bit(uint64_t cal)
{
    // 計算有幾個bits
    int cnt = 0;
    for (int i = 0; i < 64; i++)
    {
        cnt = cnt + (cal & 1);
        cal = cal >> 1;
    }
    return cnt;
}

void print_bit(uint64_t cal)
{
    for (int i = 0; i < 64; i++)
    {
        if (cal & 1)
        {
            printf("1 ");
        }
        else
        {
            printf("0 ");
        }
        cal >>= 1;
    }
    printf("\n");
}

int main()
{
    char input[1024], board[65][2];
    uint64_t score = 0;
    unsigned int outter = 0;
    int batter_situ[10][3];

    // init char array
    for (int i = 0; i < 65; i++)
    {
        board[i][0] = '\0';
        board[i][1] = '\0';
    }
    // init int array
    for (int i = 0; i < 10; i++)
    {
        batter_situ[i][0] = 0;
        batter_situ[i][1] = 0;
    }

    for (int i = 1; i <= 9; i++)
    {
        fgets(input, 1024, stdin);
        read_input(board, input, &outter, i);
    }

    game(board, &score, &outter, batter_situ);

    // 補上打擊者到[i][2]
    for (int i = 1; i < 10; i++)
    {
        batter_situ[i][2] = i;
    }

    // 改變優修順序並放入batter_to_int陣列
    int batter_to_int[10];
    for (int i = 1; i < 10; i++)
    {
        batter_to_int[i] = batter_situ[i][1] * 100 + batter_situ[i][0] * 10 + batter_situ[i][2];
    }

    selectionSort(batter_to_int);
    first_index_sort(batter_to_int);

    // print score
    score = score & ~15;
    int a = calculat_bit(score);
    printf("%d\n", a);

    //print batters
    for (int i = 1; i < 10; i++)
    {
        printf("%d %d %d\n", batter_to_int[i] % 10, (batter_to_int[i] / 10) % 10, (batter_to_int[i] / 100) % 10);
    }

    return 0;
}

int read_input(char board[65][2], char input[1024], unsigned int *outter_count, int batter)
{
    int hits;
    hits = input[0] - '0';
    for (int i = 0; i < hits; i++)
    { // 丟5個打擊狀況
        char a, b;
        a = input[3 * i + 2]; // 數字
        b = input[3 * i + 3]; // 英文
        board[batter + 9 * i][0] = a;
        board[batter + 9 * i][1] = b;
    }

    return 0;
}

int game(char board[65][2], uint64_t *b, unsigned int *outter_count, int batter_situ[10][3])
{
    int j, point = 0;
    uint64_t temp = 0, cal_point = 0;
    for (int i = 1; i < 65; i++)
    {
        unsigned int rbi = 0; // 存打點數
        temp = (*b) & 15;     // 清空計算temp >> 每次換人清空 每個打擊者壘包況狀
        j = i % 9;            // 存在對的格子(餘數為1存1 (1號打擊者) )
        if (j % 9 == 0)
            j = 9;
        if (board[i][1] == 'O')
        {
            *outter_count += 1;
            if (*outter_count % 3 == 0)
            {
                *b = (*b) & ~15;
                temp = temp & ~15;
            }
        }
        if (board[i][1] == 'B')
        {
            batter_situ[j][0]++;
            switch (board[i][0])
            {
            case '1':
                (*b)++;
                *b = *b << 1;
                (temp)++;
                temp = temp << 1;
                break;
            case '2':
                (*b)++;
                *b = *b << 2;
                (temp)++;
                temp = temp << 2;
                break;
            case '3':
                (*b)++;
                *b = *b << 3;
                (temp)++;
                temp = temp << 3;
                break;
            }
        }
        if (board[i][1] == 'R')
        {
            (*b)++;
            *b = *b << 4;
            (temp)++;
            temp = temp << 4;
            batter_situ[j][0]++;
        }
        rbi = __builtin_popcount(temp & ~15);

        cal_point = temp & ~15;

        // 安打次數
        point = __builtin_popcountl(cal_point);
        batter_situ[j][1] += point;
    }
    return 0;
}