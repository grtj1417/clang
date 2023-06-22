#include <stdio.h>

#define MAX_SIZE 100

void bubble_sort(int arr[][3], int n);

int main() {
    int arr[MAX_SIZE][3];
    int n = 0;

    // 读取输入数据
    while (scanf("%d %d %d", &arr[n][0], &arr[n][1], &arr[n][2]) == 3) {
        n++;
    }

    // 使用冒泡排序法对数据进行排序
    bubble_sort(arr, n);

    // 输出排序后的数据
    for (int i = 0; i < n; i++) {
        printf("%d %d %d\n", arr[i][0], arr[i][1], arr[i][2]);
    }

    return 0;
}

void bubble_sort(int arr[][3], int n) {
    for (int i = 0; i < n-1; i++) {
        for (int j = 0; j < n-i-1; j++) {
            if (arr[j][1] < arr[j+1][1] || (arr[j][1] == arr[j+1][1] && arr[j][2] < arr[j+1][2])) {
                // 如果前一个数的第二个元素小于后一个数的第二个元素
                // 或者前一个数的第二个元素等于后一个数的第二个元素
                // 且前一个数的第三个元素小于后一个数的第三个元素
                // 则交换两个数的位置
                int temp[3];
                temp[0] = arr[j][0];
                temp[1] = arr[j][1];
                temp[2] = arr[j][2];
                arr[j][0] = arr[j+1][0];
                arr[j][1] = arr[j+1][1];
                arr[j][2] = arr[j+1][2];
                arr[j+1][0] = temp[0];
                arr[j+1][1] = temp[1];
                arr[j+1][2] = temp[2];
            }
        }
    }
}
