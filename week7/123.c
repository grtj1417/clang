#include <stdio.h>
#include <string.h>
#include <stdlib.h>
/*typedef struct vs struct */
struct a{
    int no;
    char name[10];
};

typedef struct b{
    int no;
    char name[10];
}b_t;

typedef struct list{
    int num;
    struct list *next;
}list_t;

int main()
{
    list_t *head = malloc(sizeof(list_t));

    head->next = NULL;
    head->num = 3;
    printf("%d", head->num);
    // b_t my_b;
    // strcpy(my_b.name, "123456789");
    // my_b.no = 8787;
    // printf("%s\n", my_b.name);
    // printf("%d\n", my_b.no);
    return 0;
}