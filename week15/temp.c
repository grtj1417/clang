#include <stdio.h>
#include <stdlib.h>

struct myStruct {
    void (*fp)(int, char);
    int myint;
    char mychar;
};
void worker(int integer, char character)
{
    printf("%d %c \n", integer, character);
    return EXIT_SUCCESS;
}
void otherworker(int integer, char character)
{
    printf("dec = %d char = %c\n",integer, character);
    return EXIT_SUCCESS;
}
int main()
{
    struct myStruct *Ms = malloc(sizeof(struct myStruct));

    Ms->fp = worker; //otherworker
    Ms->myint = 50;
    Ms->mychar = 'c';
    Ms->fp(Ms->myint, Ms->mychar);
    exit(EXIT_SUCCESS);
}
/* circle, square, ... 都會吃到長度或是同樣的參數，只有裡面的十座細節不一樣，所以只需要更改 function pointer*/