#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    struct Node* next;
};

// 创建新节点
struct Node* createNode(int data) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}

// 在链表头部插入节点
void insertAtBeginning(struct Node** head, int data) {
    struct Node* newNode = createNode(data);
    newNode->next = *head;
    *head = newNode;
}

// 在链表中间插入节点
void insertAtMiddle(struct Node* prevNode, int data) {
    if (prevNode == NULL) {
        printf("前一个节点不能为空！");
        return;
    }

    struct Node* newNode = createNode(data);
    newNode->next = prevNode->next;
    prevNode->next = newNode;
}

// 在链表末尾插入节点
void insertAtEnd(struct Node** head, int data) {
    struct Node* newNode = createNode(data);
    struct Node* last = *head;

    if (*head == NULL) {
        *head = newNode;
        return;
    }

    while (last->next != NULL) {
        last = last->next;
    }

    last->next = newNode;
}

// 从链表中删除节点
void deleteNode(struct Node** head, int key) {
    struct Node* temp = *head;
    struct Node* prev = NULL;

    if (temp != NULL && temp->data == key) {
        *head = temp->next;
        free(temp);
        return;
    }

    while (temp != NULL && temp->data != key) {
        prev = temp;
        temp = temp->next;
    }

    if (temp == NULL) {
        return;
    }

    prev->next = temp->next;
    free(temp);
}

// 删除整个链表
void deleteList(struct Node** head) {
    struct Node* current = *head;
    struct Node* next;

    while (current != NULL) {
        next = current->next;
        free(current);
        current = next;
    }

    *head = NULL;
}

// 打印链表的内容
void printList(struct Node* node) {
    while (node != NULL) {
        printf("%d ", node->data);
        node = node->next;
    }
    printf("\n");
}

int main() {
    struct Node* head = NULL;
    int choice, data, key;

    while (1) {
        // printf("选择操作:\n");
        // printf("1. 在链表头部插入节点\n");
        // printf("2. 在链表中间插入节点\n");
        // printf("3. 在链表末尾插入节点\n");
        // printf("4. 从链表中删除节点\n");
        // printf("5. 删除整个链表\n");
        // printf("6. 打印链表内容\n");
        // printf("7. 退出\n");

        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("insert value:");
                scanf("%d", &data);
                insertAtBeginning(&head, data);
                break;
            case 2:
                printf("insert value:");
                scanf("%d", &data);
                printf("preNode:");
                scanf("%d", &key);
                insertAtMiddle(head, data);
                break;
            case 3:
                printf("insert value:");
                scanf("%d", &data);
                insertAtEnd(&head, data);
                break;
            case 4:
                printf("delete value:");
                scanf("%d", &data);
                deleteNode(&head, data);
                break;
            case 5:
                deleteList(&head);
                // printf("链表已被删除\n");
                break;
            case 6:
                printf("print list:");
                printList(head);
                break;
            case 7:
                exit(0);
            default:
                printf("invalid\n");
        }
    }

    return 0;
}
