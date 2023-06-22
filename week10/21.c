#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// 定義結構體用於儲存英文字和其出現次數
typedef struct {
    char word[100];
    int count;
} WordFrequency;

// 函式: 文字取代
void replaceText(char *article, char *p, char *q) {
    char *ptr = strstr(article, p);
    while (ptr != NULL) {
        strncpy(ptr, q, strlen(q));
        ptr = strstr(article, p);
    }
}

// 函式: 文字前插入
void insertBeforeText(char *article, char *p, char *q) {
    char *ptr = strstr(article, p);
    while (ptr != NULL) {
        memmove(ptr + strlen(q), ptr, strlen(ptr) + 1);
        strncpy(ptr, q, strlen(q));
        ptr = strstr(ptr + strlen(q) + strlen(p), p);
    }
}

// 函式: 文字後插入
void insertAfterText(char *article, char *p, char *q) {
    char *ptr = strstr(article, p);
    while (ptr != NULL) {
        memmove(ptr + strlen(p) + strlen(q), ptr + strlen(p), strlen(ptr + strlen(p)) + 1);
        strncpy(ptr + strlen(p), q, strlen(q));
        ptr = strstr(ptr + strlen(p) + strlen(q), p);
    }
}

// 函式: 文字刪除
void deleteText(char *article, char *p) {
    char *ptr = strstr(article, p);
    while (ptr != NULL) {
        memmove(ptr, ptr + strlen(p), strlen(ptr + strlen(p)) + 1);
        ptr = strstr(ptr, p);
    }
}

// 函式: 比較函式，用於排序 WordFrequency 結構體
int compareWordFrequency(const void *a, const void *b) {
    WordFrequency *word1 = (WordFrequency *)a;
    WordFrequency *word2 = (WordFrequency *)b;
    if (word1->count != word2->count) {
        return word2->count - word1->count;
    } else {
        return strcmp(word1->word, word2->word);
    }
}

// 函式: 文字頻率
void analyzeFrequency(char *article) {
    WordFrequency frequencies[1000];
    int totalWords = 0;

    char *word = strtok(article, " ");
    while (word != NULL) {
        int i;
        for (i = 0; i < totalWords; i++) {
            if (strcmp(word, frequencies[i].word) == 0) {
                frequencies[i].count++;
                break;
            }
        }
        if (i == totalWords) {
            strcpy(frequencies[totalWords].word, word);
            frequencies[totalWords].count = 1;
            totalWords++;
        }

        word = strtok(NULL, " ");
    }

    // 使用快速排序對文字頻率進行排序
    qsort(frequencies, totalWords, sizeof(WordFrequency), compareWordFrequency);

    // 輸出排序後的文字頻率結果
    for (int i = 0; i < totalWords; i++) {
        printf("%s,%d\n", frequencies[i].word, frequencies[i].count);
    }
}

int main() {
    char article[10000];
    char p[100];
    char q[100];

    fgets(article, sizeof(article), stdin);
    fgets(p, sizeof(p), stdin);
    fgets(q, sizeof(q), stdin);

    // 移除文章中的換行符號
    article[strcspn(article, "\n")] = '\0';

    char modifiedArticle[10000];
    strcpy(modifiedArticle, article);

    // 進行文字取代
    replaceText(modifiedArticle, p, q);
    printf("%s\n", modifiedArticle);

    strcpy(modifiedArticle, article);

    // 進行文字前插入
    insertBeforeText(modifiedArticle, p, q);
    printf("%s\n", modifiedArticle);

    strcpy(modifiedArticle, article);

    // 進行文字後插入
    insertAfterText(modifiedArticle, p, q);
    printf("%s\n", modifiedArticle);

    strcpy(modifiedArticle, article);

    // 進行文字刪除
    deleteText(modifiedArticle, p);
    printf("%s\n", modifiedArticle);

    // 進行文字頻率分析
    analyzeFrequency(article);

    return 0;
}
