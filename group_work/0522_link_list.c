#include <stdio.h>
#include <stdlib.h>
struct Node {
    int data; struct Node* next;
};
struct Node* createNode(int data) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}
int main() {
    struct Node* head = NULL; // 建立動態串列

    // 插入新資料複雜度：O(1)
    struct Node* newNode = createNode(1);
    newNode->next = head; head = newNode;

    // 搜尋資料複雜度：O(n)
    int target = 1, index = -1, i = 0; struct Node* current = head;
    while (current != NULL) {
        if (current->data == target) {
            index = i;
            break;
        }
        current = current->next;
        i++;
    }

    // 排序資料複雜度：O(n^2)
    struct Node* current1 = head;
    while (current1 != NULL) {
        struct Node* current2 = current1->next;
        while (current2 != NULL) {
            if (current1->data > current2->data) {
                int temp = current1->data;
                current1->data = current2->data;
                current2->data = temp;
            }
            current2 = current2->next;
        }
        current1 = current1->next;
    }
    return 0;
}