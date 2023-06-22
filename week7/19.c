#include <stdio.h>
#include <stdlib.h>

#define initarray(arr)                   \
    {                                    \
        for (int i = 0; i < 15; i++)     \
        {                                \
            for (int j = 0; j < 15; j++) \
            {                            \
                arr[i][j] = 0;           \
            }                            \
        }                                \
    }

int check_top(int board[15][15], int row, int col, int size)
{
    int count = 0;
    --row;
    for (; row < size && col < size && row >= 0 && col >= 0; row--)
    {
        if (board[row][col])
            count++;
    }
    return count;
}

int check_bot(int board[15][15], int row, int col, int size)
{
    int count = 0;
    row++;
    for (; row < size && col < size && row >= 0 && col >= 0; row++)
    {
        if (board[row][col])
            count++;
    }
    return count;
}

int check_left(int board[15][15], int row, int col, int size)
{
    int count = 0;
    --col;
    for (; row < size && col < size && row >= 0 && col >= 0; col--)
    {
        if (board[row][col])
            count++;
    }
    return count;
}

int check_right(int board[15][15], int row, int col, int size)
{
    int count = 0;
    col++;
    for (; row < size && col < size && row >= 0 && col >= 0; col++)
    {
        if (board[row][col])
            count++;
    }
    return count;
}

int check_top_left(int board[15][15], int row, int col, int size)
{
    int count = 0;
    --row;
    --col;
    for (; row < size && col < size && row >= 0 && col >= 0; row--, col--)
    {
        if (board[row][col])
            count++;
    }
    return count;
}

int check_top_right(int board[15][15], int row, int col, int size)
{
    int count = 0;
    --row;
    ++col;
    for (; row < size && col < size && row >= 0 && col >= 0; row--, col++)
    {
        if (board[row][col])
            count++;
    }
    return count;
}

int check_bot_left(int board[15][15], int row, int col, int size)
{
    int count = 0;
    ++row;
    --col;
    for (; row < size && col < size && row >= 0 && col >= 0; row++, col--)
    {
        if (board[row][col])
            count++;
    }
    return count;
}

int check_bot_right(int board[15][15], int row, int col, int size)
{
    int count = 0;
    ++row;
    ++col;
    for (; row < size && col < size && row >= 0 && col >= 0; row++, col++)
    {
        if (board[row][col])
            count++;
    }
    return count;
}

int main()
{
    int size;
    scanf("%d", &size);
    int board[15][15];
    initarray(board);

    for (int row = 0; row < size; row++)
    {
        for (int col = 0; col < size; col++)
        {
            scanf("%d", &board[row][col]);
        }
    }

    int count = 0;

    for (int row = 0; row < size; row++)
    {
        for (int col = 0; col < size; col++)
        {
            if (board[row][col])
            { // 代表上面有皇后
                count += check_top(board, row, col, size);
                count += check_bot(board, row, col, size);
                count += check_left(board, row, col, size);
                count += check_right(board, row, col, size);
                count += check_top_left(board, row, col, size);
                count += check_top_right(board, row, col, size);
                count += check_bot_left(board, row, col, size);
                count += check_bot_right(board, row, col, size);
                // printf("%d", board[row][col]);
            }
        }
    }
    if(!count){
        printf("There is no attack.");
    }else printf("%d", count/2);
    return 0;
}