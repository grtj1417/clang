#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define STACK_LEN 1024
struct birthday
{
    int year, month, date;
};

typedef struct node_s
{
    char name[500];
    int age;
    struct birthday birth;
    struct node_s *next;
} node;

node *init_node(char *name, int age, struct birthday birth)
{
    node *newNode = (node *)malloc(sizeof(node));
    if (!newNode)
        return NULL; // 除錯

    strcpy(newNode->name, name); // 定義name
    newNode->age = age;
    newNode->birth = birth;
    newNode->next = NULL;

    return newNode;
}

node *push(node *stack, node *newNode)
{
    newNode->next = stack;
    return newNode;
}

node *pop(node **stack)
{
    if (!(*stack))
        return NULL;

    if (!(*stack)->next) {// 只有一個元素
        node *returnValue = *stack;
        *stack = NULL;
        return returnValue;
    }

    node *returnValue = *stack;
    *stack = (*stack)->next;
    returnValue->next = NULL;
    return returnValue;
}

bool stackIsEmpty(node *stack)
{
    if (!stack)
        return true;
    return false;
}

void printNode(node *node_p)
{
    printf("%s %d %d_%d_%d\n", node_p->name, node_p->age, node_p->birth.year, node_p->birth.month, node_p->birth.date);
}

int main()
{
    node *stack = NULL;
    int command;
    while (scanf("%d", &command) == 1)
    {
        if (command == 1)
        {
            char name[500];
            int age, year, month, date;
            scanf("%s %d %d %d %d", name, &age, &year, &month, &date);

            struct birthday birth;
            birth.date = date;
            birth.month = month;
            birth.year = year;

            node *newNode = init_node(name, age, birth);
            // printNode(newNode);
            stack = push(stack, newNode);
        }
        else if (command == 2)
        {
            int subCommand;
            scanf("%d", &subCommand);
            if (subCommand == 1)
            {
                node *popped = pop(&stack);
                if(!popped){
                    printf("The Stack is empty\n");
                    continue;
                }
                printf("%s\n", popped->name);
                free(popped);
            }
            else if (subCommand == 2)
            {
                node *popped = pop(&stack);
                if(!popped){
                    printf("The Stack is empty\n");
                    continue;
                }
                printf("%d\n", popped->age);
                free(popped);
            }
            else if (subCommand == 3)
            {
                node *popped = pop(&stack);
                if(!popped){
                    printf("The Stack is empty\n");
                    continue;
                }
                printf("%d_%d_%d\n", popped->birth.year, popped->birth.month, popped->birth.date);
                free(popped);
            }
            
        }else if(command == 3){
            while (!stackIsEmpty(stack))
            {
                node *popped = pop(&stack);
                printNode(popped);
                free(popped);
            }
        }else if (command == 4){
                if(stackIsEmpty(stack)){
                    printf("The Stack is empty\n");
                    continue;
                }
                for (node *itr = stack; itr; itr = itr->next)
                {
                    printNode(itr);
                }
        }else if (command == 5){
            int count = 0;
            while (!stackIsEmpty(stack))
            {
                node *popped = pop(&stack);
                count++;
                free(popped);
            }
            printf("%d", count);
            goto final;
        }
    }
final:
    return 0;
}