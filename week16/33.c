#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char name[20];
    int age;
    int year;
    int month;
    int day;
} Data;

typedef struct Node {
    Data data;
    struct Node* next;
} Node;

typedef struct {
    Node* front;
    Node* rear;
} Queue;

void initializeQueue(Queue* queue) {
    queue->front = NULL;
    queue->rear = NULL;
}

int isQueueEmpty(Queue* queue) {
    return queue->front == NULL;
}

void enqueue(Queue* queue, Data data) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = data;
    newNode->next = NULL;

    if (isQueueEmpty(queue)) {
        queue->front = newNode;
        queue->rear = newNode;
    } else {
        queue->rear->next = newNode;
        queue->rear = newNode;
    }
}

Data dequeue(Queue* queue) {
    if (isQueueEmpty(queue)) {
        Data emptyData;
        emptyData.name[0] = '\0';
        emptyData.age = 0;
        emptyData.year = 0;
        emptyData.month = 0;
        emptyData.day = 0;
        return emptyData;
    }

    Node* frontNode = queue->front;
    Data data = frontNode->data;

    queue->front = frontNode->next;
    if (queue->front == NULL) {
        queue->rear = NULL;
    }

    free(frontNode);
    return data;
}

void printQueue(Queue* queue) {
    Node* current = queue->front;
    while (current != NULL) {
        printf("%s %d %d_%d_%d\n", current->data.name, current->data.age,
                current->data.year, current->data.month, current->data.day);
        current = current->next;
    }
}

void printQueueWithoutDequeue(Queue* queue) {
    if (isQueueEmpty(queue)) {
        printf("The Queue is empty\n");
        return;
    }

    Node* current = queue->front;
    while (current != NULL) {
        printf("%s %d %d_%d_%d\n", current->data.name, current->data.age,
                current->data.year, current->data.month, current->data.day);
        current = current->next;
    }
}

int main() {
    Queue queue;
    initializeQueue(&queue);

    int command;
    while (scanf("%d", &command) == 1) {
        if (command == 1) {
            Data data;
            scanf("%s%d%d%d%d", data.name, &data.age, &data.year,
                    &data.month, &data.day);
            enqueue(&queue, data);
        } else if (command == 2) {
            int operation;
            scanf("%d", &operation);
            Data data = dequeue(&queue);
            if (data.name[0] == '\0') {
                printf("The Queue is empty\n");
            } else {
                if (operation == 1) {
                    printf("%s\n", data.name);
                } else if (operation == 2) {
                    printf("%d\n", data.age);
                } else if (operation == 3) {
                    printf("%d_%d_%d\n", data.year, data.month, data.day);
                }
            }
        } else if (command == 3) {
            Data data = dequeue(&queue);
            while (data.name[0] != '\0') {
                printf("%s %d %d_%d_%d\n", data.name, data.age, data.year,
                        data.month, data.day);
                data = dequeue(&queue);
            }
        } else if (command == 4) {
            printQueueWithoutDequeue(&queue);
        } else if (command == 5) {
            int count = 0;
            Data data = dequeue(&queue);
            while (data.name[0] != '\0') {
                count++;
                data = dequeue(&queue);
            }
            printf("%d\n", count);
            break;
        }
    }

    return 0;
}
