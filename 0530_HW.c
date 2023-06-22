#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    struct Node* next;
};

void reversePrint(struct Node* head) {
    if (head == NULL)
        return;
    
    reversePrint(head->next);
    
    printf("%d ", head->data);
}

int main() {
    struct Node* head = NULL;
    reversePrint(head);
    return 0;
}
