
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef struct {
    char word[1000];
    int frequency;
} Word;

void removeExtraSpaces(char *sentence) {
    int i, j;
    int length = strlen(sentence);
    int isPrevSpace = 0;

    for (i = 0, j = 0; i < length; i++) {
        if (isspace(sentence[i])) {
            if (isPrevSpace) {
                continue;
            }
            isPrevSpace = 1;
        } else {
            isPrevSpace = 0;
        }

        sentence[j++] = sentence[i];
    }

    sentence[j] = '\0';
}

int searchWord(const char S[], const char W[]) {
    int i, j;
    int n = strlen(S) + 1;
    int k = strlen(W);

    for (i = 0; i < n - k; i++) {
        for (j = 0; j < k; j++) {
            if (S[i + j] != W[j] || W[j] == ' ') {
                break;
            }
        }

        if (j == k && (S[i + j] == ' ' || S[i + j] == '\0')) {
            if (i == 0 || (i > 0 && S[i - 1] == ' ')) {
                return i;
            }
        }
    }

    return -1;
}

void replaceWord(char *sentence, const char *targetWord, const char *replaceWord) {
    int sizeS = strlen(sentence) + 1;
    int sizeT = strlen(targetWord);
    int sizeR = strlen(replaceWord);
    int pos = 0;

    while ((pos = searchWord(sentence, targetWord)) != -1) {
        memcpy(sentence + pos, replaceWord, sizeR);
        memmove(sentence + pos + sizeR, sentence + pos + sizeT, sizeS - pos - sizeT);
    }
}

void insertWord(char *sentence, const char *targetWord, const char *insertWord, int insertPosition) {
    int sizeS = strlen(sentence) + 1;
    int sizeI = strlen(insertWord);
    int sizeT = strlen(targetWord);

    if (insertPosition >= 0) {
        memmove(sentence + insertPosition + sizeI + 1, sentence + insertPosition + sizeT, sizeS - insertPosition - sizeT);
        memcpy(sentence + insertPosition, insertWord, sizeI);
        sentence[insertPosition + sizeI] = ' ';
    }
}

void deleteWord(char *sentence, const char *targetWord) {
    int sizeS = strlen(sentence) + 1;
    int sizeT = strlen(targetWord);
    int pos = 0;

    while ((pos = searchWord(sentence, targetWord)) != -1) {
        memmove(sentence + pos, sentence + pos + sizeT, sizeS - pos - sizeT);
    }
}

void analyzeWordFrequency(const char *sentence) {
    char *sentenceCopy = strdup(sentence);  // Create a non-const copy
    Word words[1000];
    int wordCount = 0;

    char *word = strtok(sentenceCopy, " ");
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

    // Print word frequency
    printf("Word Frequency:\n");
    for (int i = 0; i < wordCount; i++) {
        printf("%s: %d\n", words[i].word, words[i].frequency);
    }

    free(sentenceCopy);  // Free the dynamically allocated memory
}


int main() {
    char sentence[1000];
    char targetWord[50];
    char insertWord[50];

    fgets(sentence, sizeof(sentence), stdin);
    sentence[strcspn(sentence, "\n")] = '\0';

    scanf("%s", targetWord);

    scanf("%s", insertWord);

    int i=searchWord(sentence,targetWord);

    char modifiedSentence_0[1000];
    strcpy(modifiedSentence_0, sentence);
    replaceWord(modifiedSentence_0, targetWord, insertWord);

    char modifiedSentence_1[1000];
    strcpy(modifiedSentence_1, sentence);
    insertBeforeWord(modifiedSentence_1, targetWord, insertWord);
    printf("%s\n",modifiedSentence_1);

    char modifiedSentence_2[1000];
    strcpy(modifiedSentence_2, sentence);
    insertAfterWord(modifiedSentence_2, targetWord, insertWord);
    printf("%s\n",modifiedSentence_2);

    char modifiedSentence_3[1000];
    strcpy(modifiedSentence_3, sentence);
    deleteTargetWord(modifiedSentence_3,targetWord);
    normalizeSpaces(modifiedSentence_3);
    removeLeadingSpace(modifiedSentence_3);
    printf("%s\n",modifiedSentence_3);

    char modifiedSentence_4[1000];
    strcpy(modifiedSentence_4, sentence);
    analyzeWordFrequency(modifiedSentence_4);


    return 0;
}
