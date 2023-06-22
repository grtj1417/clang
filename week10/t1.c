#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char word[100];
    int frequency;
} Word;

int compareWords(const void *a, const void *b) {
    const Word *wordA = (const Word *)a;
    const Word *wordB = (const Word *)b;

    if (wordA->frequency == wordB->frequency) {
        return strcmp(wordA->word, wordB->word);
    }

    return wordB->frequency - wordA->frequency;
}

char *replaceWord(char *sentence, const char *target, const char *replacement) {
    int targetLen = strlen(target);
    int replacementLen = strlen(replacement);

    char *result = (char *)malloc(10000 * sizeof(char));
    char *ptr = sentence;
    char *temp;

    while ((temp = strstr(ptr, target)) != NULL) {
        strncpy(result, ptr, temp - ptr);
        result += temp - ptr;
        strcpy(result, replacement);
        result += replacementLen;
        ptr = temp + targetLen;
    }

    strcpy(result, ptr);
    return sentence;
}

char *insertBeforeWord(char *sentence, const char *target, const char *insertion) {
    char *result = (char *)malloc(10000 * sizeof(char));
    char *temp = strstr(sentence, target);

    strncpy(result, sentence, temp - sentence);
    result += temp - sentence;
    strcpy(result, insertion);
    result += strlen(insertion);
    strcpy(result, temp);

    return sentence;
}

char *insertAfterWord(char *sentence, const char *target, const char *insertion) {
    char *result = (char *)malloc(10000 * sizeof(char));
    char *temp = strstr(sentence, target);
    int targetLen = strlen(target);

    strncpy(result, sentence, temp - sentence + targetLen);
    result += temp - sentence + targetLen;
    strcpy(result, insertion);
    result += strlen(insertion);
    strcpy(result, temp + targetLen);

    return sentence;
}

char *deleteWord(char *sentence, const char *target) {
    char *result = (char *)malloc(10000 * sizeof(char));
    char *temp = strstr(sentence, target);
    int targetLen = strlen(target);

    strncpy(result, sentence, temp - sentence);
    result += temp - sentence;
    strcpy(result, temp + targetLen);

    return sentence;
}

void analyzeWordFrequency(char *sentence) {
    Word words[1000];
    int wordCount = 0;

    char *word = strtok(sentence, " ");
    while (word != NULL) {
        int i;
        for (i = 0; i < wordCount; i++) {
            if (strcmp(words[i].word, word) == 0) {
                words[i].frequency++;
                break;
            }
        }

        if (i == wordCount) {
            strcpy(words[wordCount].word, word);
            words[wordCount].frequency = 1;
            wordCount++;
        }

        word = strtok(NULL, " ");
    }

    qsort(words, wordCount, sizeof(Word), compareWords);

    for (int i = 0; i < wordCount; i++) {
        printf("%s,%d\n", words[i].word, words[i].frequency);
    }
}

int main() {
    char sentence[10000];
    char target[100];
    char replacement[100];

    fgets(sentence, sizeof(sentence), stdin);
    sentence[strlen(sentence) - 1] = '\0';

    fgets(target, sizeof(target), stdin);
    target[strlen(target) - 1] = '\0';

    fgets(replacement, sizeof(replacement), stdin);
    replacement[strlen(replacement) - 1] = '\0';

    char *replaced = replaceWord(strdup(sentence), target, replacement);
    char *insertedBefore = insertBeforeWord(strdup(sentence), target, replacement);
    char *insertedAfter = insertAfterWord(strdup(sentence), target, replacement);
    char *deleted = deleteWord(strdup(sentence), target);

    printf("%s\n", replaced);
    printf("%s\n", insertedBefore);
    printf("%s\n", insertedAfter);
    printf("%s\n", deleted);

    analyzeWordFrequency(sentence);

    return 0;
}
