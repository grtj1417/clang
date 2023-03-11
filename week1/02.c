#include <stdio.h>

int calculat_bit(unsigned int cal)
{
    // 正整數 他會計算有幾個bits
    int cnt = 0;
    for(int i = 0; i < 32; i++) {
        cnt = cnt + (cal & 1);
        cal = cal >> 1;
    }
    return cnt;
}

void print_bit(unsigned int cal);


int main()
{
    unsigned int score_count = 0, outter_count = 0 , b = 0 , player = 0;
    unsigned char input;
    for (int i = 0; i < 5; i++)
    {
        scanf(" %c", &input);
        switch (input){
        case 'O':
            outter_count += 1;
            if (outter_count >= 3)
                b = b & ~15;
            break;
        case '1':
            b++;
            b = b << 1;
            break;
        case '2':
            b++;
            b = b << 2;
            break;
        case '3':
            b++;
            b = b << 3;
            break;
        case 'H':
            b++;
            b = b << 4;
            break;
        }
    }
    score_count = b & ~(15);
    score_count = calculat_bit(score_count);
    printf("%d\n", score_count);
    unsigned int final_board = b & 15;
    printf("%d %d %d",(final_board >> 1) & 1, (final_board >> 2) & 1, (final_board >> 3) & 1);
    return 0;
}
void print_bit(unsigned int cal)
{
    for(int i = 0; i < 32; i++) {
        if(cal & 1){
            printf("1 ");
        } else {
            printf("0 ");
        }
        cal >>= 1;
    }
    printf("\n");
}


