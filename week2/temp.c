#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#define print(x) \
    printf("%d %d %d\n", (x >> 1) & 1, (x >> 2) & 1, (x >> 3) & 1);

#define init_board(board)        \
    for (int i = 0; i < 25; i++) \
    {                            \
        board[i][0] = '\0';      \
        board[i][1] = '\0';      \
    }

#define play_game(team)                                      \
    for (int i = 0; i < 5; i++)                              \
    {                                                        \
        gets(input);                                         \
        read_input(board, input, &score_##team, &outter, i); \
    }                                                        \
    outter = 0;                                              \
    game(board, &score_##team, &outter);

int read_input(char board[25][2], char input[1024], unsigned int *score, unsigned int *outter_count, int batter);
int game(char board[25][2], unsigned int *b, unsigned int *outter_count);

int main()
{
    char input[1024], board[25][2];
    unsigned int score_a = 0, score_b = 0, outter = 0;

    // A隊
    init_board(board);
    play_game(a);

    // B隊
    init_board(board);
    play_game(b);

    unsigned int final_board_a = score_a & 15;
    unsigned int final_board_b = score_b & 15;
    score_a = score_a & ~15;
    score_b = score_b & ~15;

    int a = __builtin_popcount(score_a), b = __builtin_popcount(score_b);
    printf("%d\n", a);
    print(final_board_a);
    printf("%d\n", b);
    print(final_board_b);

    if (a == b)
        printf("Tie");
    else if (a > b)
        printf("A");
    else
        printf("B");
    return 0;
}

int read_input(char board[25][2], char input[1024], unsigned int *score, unsigned int *outter_count, int batter)
{
    int hits;
    hits = input[0] - '0';
    for (int i = 0; i < hits; i++)
    { // 丟5個打擊狀況
        char a, b;
        a = input[3 * i + 2]; // 數字
        b = input[3 * i + 3]; // 英文
        board[batter + 5 * i][0] = a;
        board[batter + 5 * i][1] = b;
    }
    return 0;
}

int game(char board[25][2], unsigned int *b, unsigned int *outter_count)
{
    for (int i = 0; i < 25; i++)
    {
        if (board[i][1] == 'O')
        {
            *outter_count += 1;
            if (*outter_count == 3 || *outter_count == 6)
            {
                *b = (*b) & ~15;
            }
        }
        if (board[i][1] == 'B')
        {
            switch (board[i][0])
            {
            case '1':
                (*b)++;
                *b = *b << 1;
                break;
            case '2':
                (*b)++;
                *b = *b << 2;
                break;
            case '3':
                (*b)++;
                *b = *b << 3;
                break;
            }
        }
        if (board[i][1] == 'R')
        {
            (*b)++;
            *b = *b << 4;
        }
    }
    return 0;
}