#include <stdio.h>
#define N 3

//在外面宣告
int dice[N][6] = {{4, 1, 3, 6, 2, 5},
                    {4, 1, 3, 6, 2, 5},
                    {4, 1, 3, 6, 2, 5}};

void swap(int i, int j)
{
    int temp[6];
    for (int k = 0; k < 6; k++)
        temp[k] = dice[i][k];
    for (int k = 0; k < 6; k++)
        dice[i][k] = dice[j][k];
    for (int k = 0; k < 6; k++)
        dice[j][k] = temp[k];
}

void roll(int i, int index)
{
    int temp;
    switch (i)
    {
    case 1://前
        temp = dice[index][0];
        dice[index][0] = dice[index][1];
        dice[index][1] = dice[index][2];
        dice[index][2] = dice[index][3];
        dice[index][3] = temp;
        break;
    case 2://左
        temp = dice[index][5];
        dice[index][5] = dice[index][1];
        dice[index][1] = dice[index][4];
        dice[index][4] = dice[index][3];
        dice[index][3] = temp;
        break;
    case 3://右
        temp = dice[index][3];
        dice[index][3] = dice[index][4];
        dice[index][4] = dice[index][1];
        dice[index][1] = dice[index][5];
        dice[index][5] = temp;
        break;
    default:
        break;
    }
}

int main()
{
    int n;
    scanf("%d", &n);
    for (int i = 0; i < n; i++)
    {
        char c1, c2;
        scanf(" %c %c", &c1, &c2);
        int idx1, idx2;
        switch (c1)
        {
        case 'L':
            idx1 = 0;
            break;
        case 'M':
            idx1 = 1;
            break;
        case 'R':
            idx1 = 2;
            break;
        default:
            break;
        }
        switch (c2)
        {
        case '1':
            roll(1, idx1);
            break;
        case '2':
            roll(2, idx1);
            break;
        case '3':
            roll(3, idx1);
            break;
        case 'L':
            idx2 = 0;
            swap(idx1, idx2);
            break;
        case 'M':
            idx2 = 1;
            swap(idx1, idx2);
            break;
        case 'R':
            idx2 = 2;
            swap(idx1, idx2);
            break;
        default:
            break;
        }
    }
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < 6; j++)
        {
            printf("%d ", dice[i][j]);
        }
        printf("\n");
    }
    return 0;
}
