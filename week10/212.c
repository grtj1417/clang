#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_WORDS 1000
#define MAX_WORD_LEN 50

// 函数：文字取代
void replaceWord(char *str, const char *oldWord, const char *newWord) {
    int oldWordLen = strlen(oldWord);
    int newWordLen = strlen(newWord);
    int diff = newWordLen - oldWordLen;

    char *pos = strstr(str, oldWord);
    while (pos != NULL) {
        memmove(pos + newWordLen, pos + oldWordLen, strlen(pos + oldWordLen) + 1);
        memcpy(pos, newWord, newWordLen);
        pos = strstr(pos + newWordLen, oldWord);
    }
}

// 函数：文字前插入
void insertBefore(char *str, const char *insertPos, const char *insertStr) {
    int insertPosLen = strlen(insertPos);
    int insertStrLen = strlen(insertStr);
    int totalLen = strlen(str) + insertStrLen;

    char *pos = strstr(str, insertPos);
    if (pos != NULL) {
        char *tempStr = (char *)malloc(totalLen + 1);
        strncpy(tempStr, str, pos - str);
        tempStr[pos - str] = '\0';
        strcat(tempStr, insertStr);
        strcat(tempStr, pos);
        strcpy(str, tempStr);
        free(tempStr);
    }
}

// 函数：文字后插入
void insertAfter(char *str, const char *insertPos, const char *insertStr) {
    int insertPosLen = strlen(insertPos);
    int insertStrLen = strlen(insertStr);
    int totalLen = strlen(str) + insertStrLen;

    char *pos = strstr(str, insertPos);
    if (pos != NULL) {
        char *tempStr = (char *)malloc(totalLen + 1);
        strncpy(tempStr, str, pos - str + insertPosLen);
        tempStr[pos - str + insertPosLen] = '\0';
        strcat(tempStr, insertStr);
        strcat(tempStr, pos + insertPosLen);
        strcpy(str, tempStr);
        free(tempStr);
    }
}

// 函数：文字删除
void deleteWord(char *str, const char *word) {
    int wordLen = strlen(word);

    char *pos = strstr(str, word);
    while (pos != NULL) {
        memmove(pos, pos + wordLen, strlen(pos + wordLen) + 1);
        pos = strstr(pos, word);
    }
}

// 比较函数：用于单词频率排序
int compareWordFrequency(const void *a, const void *b) {
    const char *wordA = *(const char **)a;
    const char *wordB = *(const char **)b;

    return strcmp(wordB, wordA); // 逆序排列
}

// 函数：文字频率排序
void sortByFrequency(char *str) {
    char *words[MAX_WORDS];
    int frequencies[MAX_WORDS] = {0};
    int wordCount = 0;

    // 分割单词
    char *word = strtok(str, " ");
    while (word != NULL) {
        int found = 0;
        for (int i = 0; i < wordCount; i++) {
            if (strcmp(words[i], word) == 0) {
                frequencies[i]++;
                found = 1;
                break;
            }
        }
        if (!found) {
            words[wordCount] = strdup(word);
            frequencies[wordCount] = 1;
            wordCount++;
        }
        word = strtok(NULL, " ");
    }

    // 排序
    qsort(words, wordCount, sizeof(char *), compareWordFrequency);

    // 输出结果
    for (int i = 0; i < wordCount; i++) {
        printf("%s ", words[i]);
    }
    printf("\n");

    // 释放内存
    for (int i = 0; i < wordCount; i++) {
        free(words[i]);
    }
}

int main() {
    char article[MAX_WORDS];
    char p[MAX_WORD_LEN];
    char q[MAX_WORD_LEN];

    // 输入文章、P和Q
    fgets(article, sizeof(article), stdin);
    article[strcspn(article, "\n")] = '\0';

    fgets(p, sizeof(p), stdin);
    p[strcspn(p, "\n")] = '\0';

    fgets(q, sizeof(q), stdin);
    q[strcspn(q, "\n")] = '\0';

    // 文字取代
    replaceWord(article, p, q);
    printf("%s\n", article);

    // 文字前插入
    char insertBeforeResult[MAX_WORDS];
    strcpy(insertBeforeResult, article);
    insertBefore(insertBeforeResult, p, q);
    printf("%s\n", insertBeforeResult);

    // 文字后插入
    char insertAfterResult[MAX_WORDS];
    strcpy(insertAfterResult, article);
    insertAfter(insertAfterResult, p, q);
    printf("%s\n", insertAfterResult);

    // 文字删除
    deleteWord(article, p);
    printf("%s\n", article);

    // 文字频率排序
    sortByFrequency(article);

    return 0;
}
