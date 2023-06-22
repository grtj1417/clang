#include <stdio.h>

int dice[3][6] = {{4,1,3,6,2,5},{4,1,3,6,2,5},{4,1,3,6,2,5}};

void SWAP(int i, int j){
    int temp[6];
    for(int k = 0; k < 6; k++){
        temp[k] = dice[i][k];
        dice[i][k] = dice[j][k];
        dice[j][k] = temp[k];
    }
}

void roll(int idx, int input_number)
{
    int temp;
    switch (input_number)
    {
    case 1:
        temp = dice[idx][0];
        dice[idx][0] = dice[idx][1];
        dice[idx][1] = dice[idx][2];
        dice[idx][2] = dice[idx][3];
        dice[idx][3] = temp;
        break;
    case 2:
        temp = dice[idx][5];
        dice[idx][5] = dice[idx][1];
        dice[idx][1] = dice[idx][4];
        dice[idx][4] = dice[idx][3];
        dice[idx][3] = temp;
        break;
    case 3:
        temp = dice[idx][3];
        dice[idx][3] = dice[idx][4];
        dice[idx][4] = dice[idx][1];
        dice[idx][1] = dice[idx][5];
        dice[idx][5] = temp;
        break;
    default:
        break;
    }

}

int main()
{
    int n;
    scanf("%d\n", &n);
    char c1, c2;
    int idx1, idx2;
    for(int i = 0; i < n; i++){
        scanf(" %c %c", &c1, &c2);
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
            roll(idx1, 1);
            break;
        case '2':
            roll(idx1, 2);
            break;
        case '3':
            roll(idx1, 3);
            break;
        case 'L':
            idx2 = 0;
            SWAP(idx1,idx2);
            break;
        case 'M':
            idx2 = 1;
            SWAP(idx1,idx2);
            break;
        case 'R':
            idx2 = 2;
            SWAP(idx1,idx2);
            break;
        default:
            break;
        }
    }
    for(int i = 0; i < 3; i++){
        for(int j = 0; j < 6; j++){
            printf("%d ", dice[i][j]);
        }
        printf("\n");
    }
    return 0;
}