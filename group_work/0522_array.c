#include <stdio.h>

#define MAX_SIZE 100

int main() {
    int array[MAX_SIZE]; // 建立固定大小的陣列

    // 插入新資料複雜度：O(1)
    array[0] = 1;

    // 搜尋資料複雜度：O(n)，若已知索引則為O(1)
    int target = 1;
    int index = -1;
    for (int i = 0; i < MAX_SIZE; i++) {
        if (array[i] == target) {
            index = i;
            break;
        }
    }

    // 排序資料複雜度：O(n^2)
    for (int i = 0; i < MAX_SIZE - 1; i++) {
        for (int j = 0; j < MAX_SIZE - i - 1; j++) {
            if (array[j] > array[j + 1]) {
                int temp = array[j];
                array[j] = array[j + 1];
                array[j + 1] = temp;
            }
        }
    }

    return 0;
}