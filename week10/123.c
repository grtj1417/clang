#include <stdio.h>
#include <string.h>

void insertWord_front(char* input, const char* target, const char* insert) {
    char result[100];  // 假設結果字串不會超過 100 個字元
    char* token;
    char* remaining;
    
    token = strtok(input, " ");  // 使用空格分割字串
    
    while (token != NULL) {
        if (strcmp(token, target) == 0) {
            strcat(result, insert);  // 插入單字 B
            strcat(result, " ");  // 加入空格
        }
        
        strcat(result, token);  // 將目前的單字加入結果字串
        strcat(result, " ");  // 加入空格
        
        token = strtok(NULL, " ");  // 取得下一個單字
    }
    
    printf("Result: %s\n", result);
}

void insertWord_back(char* input, const char* target, const char* insert) {
    char result[100];  // 假設結果字串不會超過 100 個字元
    char* token;
    char* remaining;
    
    token = strtok(input, " ");  // 使用空格分割字串
    
    while (token != NULL) {
        if (strcmp(token, target) == 0) {
            strcat(result, token);  // 加入目標單字
            strcat(result, " ");  // 加入空格
            strcat(result, insert);  // 插入單字 B
        }
        else {
            strcat(result, token);  // 將目前的單字加入結果字串
        }
        
        strcat(result, " ");  // 插入空格
        
        token = strtok(NULL, " ");  // 取得下一個單字
    }
    
    printf("%s\n", result);
}

int main() {
    char input[1000];
    char target[20];
    char insert[20];
    
    fgets(input, sizeof(input), stdin);
    
    scanf("%s", target);
    
    scanf("%s", insert);
    
    insertWord_front(input, target, insert);
    insertWord_back(input, target, insert);
    
    return 0;
}
