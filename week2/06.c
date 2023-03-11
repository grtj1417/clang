#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
int read_input(char board[25][2], char input[1024],unsigned int *score , unsigned int *outter_count,int batter);
int game(char board[25][2], unsigned int *b , unsigned int *outter_count);
void print_bit(unsigned int cal);

int main()
{
    char board[25][2];
    for(int i = 0; i < 25; i++){ //初始化陣列
        board[i][0]='\0';
        board[i][1]='\0';
    }
    char input[1024];
    unsigned int score_a = 0,score_b = 0,outter = 0;

    //A隊
    for (int i = 0; i < 5; i++) {
        gets(input);
        read_input(board,input, &score_a, &outter,i);
    }
    game(board, &score_a, &outter);

    for(int i = 0; i < 25; i++){ //初始化陣列
        board[i][0]='\0';
        board[i][1]='\0';
    }
    //B隊
    for (int i = 0; i < 5; i++) { 
        gets(input);
        read_input(board,input, &score_b, &outter,i);
    }
    outter = 0;
    game(board, &score_b, &outter);


    unsigned int final_board_a = score_a & 15;
    unsigned int final_board_b = score_b & 15;
    score_a = score_a & ~15;
    score_b = score_b & ~15;

    printf("%d\n", __builtin_popcount(score_a));
    printf("%d %d %d\n",(final_board_a >> 1) & 1, (final_board_a >> 2) & 1, (final_board_a >> 3) & 1);
    printf("%d\n", __builtin_popcount(score_b));
    printf("%d %d %d\n",(final_board_b >> 1) & 1, (final_board_b >> 2) & 1, (final_board_b >> 3) & 1);
    if( __builtin_popcount(score_a) ==  __builtin_popcount(score_b)){
        printf("Tie");
    }else if ( __builtin_popcount(score_a) >  __builtin_popcount(score_b)){
        printf("A");
    }else printf("B");
    return 0;
}

int read_input(char board[25][2], char input[1024],unsigned int *score , unsigned int *outter_count,int batter)
{
    int hits;
    hits = input[0] - '0';
    for(int i = 0; i < hits ;i++){ //丟5個打擊狀況
        char a , b ;
        a = input[3 * i + 2] ; //數字
        b = input[3 * i + 3] ; //英文
        board[batter + 5 * i][0] = a;
        board[batter + 5 * i][1] = b;
    }
    return 0;
}

int game(char board[25][2], unsigned int *b , unsigned int *outter_count)
{
    for(int i = 0; i < 25; i++){
        if(board[i][1] == 'O'){
            *outter_count += 1;
            if (*outter_count == 3 || *outter_count == 6){
                *b = (*b) & ~15;
            }
        }
        if(board[i][1] == 'B'){
            switch (board[i][0]){
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
        if(board[i][1] == 'R'){
            (*b)++;
            *b = *b << 4;
        }
    // print_bit(*b);
    }
    
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