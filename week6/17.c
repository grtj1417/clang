#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

int brute(int input[], int length) // 暴力法 O(n^2)
{
    int counter = 0;

    // int x[length/2]
    for (int i = 0; i < length; i++)
    {
        for (int j = i + 1; j < length; j++)
        {
            if (i < j && input[i] > input[j])
            {
                counter++;
            }
        }
    }
    return counter;
}

int divide_and_conquer(int input[], int head, int tail)
{
    if (tail - head < 2)
        return 0;
    else
    {
        int mid = (head + tail) / 2; //O(1)
        int s = 0;
        for (int i = head; i < mid; i++) //O(n)
        {
            for (int j = mid; j < tail; j++)
            {
                if (i < j && input[i] > input[j])
                    s++;
            }
        }
        return divide_and_conquer(input, head, mid) + divide_and_conquer(input, mid, tail) + s; //O(n/2+n/2+n)
    }
}

int main()
{
    int length;
    scanf("%d\n", &length);
    int input[length];

    clock_t start_t1, end_t1;
    clock_t start_t2, end_t2;
    double total_t;
    
    for (int i = 0; i < length; i++)
    {
        scanf("%d", &input[i]);
    }

    // start_t1 = clock();

    // brute(input, length);

    // end_t1 = clock();
    // printf("brute force time = %ld\n",end_t1 - start_t1);


    // start_t2 = clock();
    // divide_and_conquer(input, 0, length);

    // end_t2 = clock();
    // printf("divide_and_conquer time = %ld\n",end_t2 - start_t2);

    printf("%d", divide_and_conquer(input, 0, length));
    return 0;
}