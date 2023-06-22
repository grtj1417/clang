#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
typedef struct {
    char word[1000];
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

void normalizeSpaces(char *sentence) {
    size_t sentenceLength = strlen(sentence);
    size_t i = 0;
    int isPrevSpace = 0;  // Flag to track if the previous character was a space

    while (i < sentenceLength) {
        if (isspace(sentence[i])) {
            // If the current character is a space
            if (isPrevSpace) {
                // If the previous character was also a space, shift the sentence to remove the extra space
                memmove(&sentence[i], &sentence[i + 1], sentenceLength - i);
                sentenceLength--;
                continue;  // Skip the increment of i
            }
            isPrevSpace = 1;  // Set the flag to indicate a space
        } else {
            isPrevSpace = 0;  // Reset the flag for non-space characters
        }

        i++;
    }
    sentence[sentenceLength] = '\0';  // Add null-terminating character at the end
}

int isWordCharacter(char c) {
    return isalnum(c) || c == '_';
}

int searchWord(char S[],char W[]){
	int i,j;				//迴圈變數
	int n;					//句子長度+1('\0')
	int k;					//單詞長度
	
	n=strlen(S)+1;			//獲取句子長度+1('\0')
	k=strlen(W);			//獲取單詞長度
	
	for(i=0;i<n-k;i++){			//迴圈到n-k，因為n-k後面，找不到含有k個字元的單詞了。
		for(j=0;j<k;j++){				//迴圈單詞每個字母
			if(S[i+j]!=W[j]||W[j]==' '){		//當S[i+j]不與W[j]相等，或者單詞裡出現空格時跳出
				break;
			}
		}
		if(j==k&&(S[i+j]==' '||S[i+j]=='\0')){		
			/*j==k，表示句子裡存在與單詞完全匹配的字母(可能還不是單詞)。如String與tri此時匹配能成功。
			而S[i+j]等於' '或者'\0',表示句子後面分割或者結束。但匹配的段落前面不一定分割。
			如String與ing匹配能成功，但String與tri匹配就不能成功了。*/
			if(i==0||(i>0&&S[i-1]==' ')){		//此處判斷是否有前分割,只有句首和存在前分割的段落才是單詞
				return i;
			}
		}
	}
	return -1;
}

void replaceWord(char S[], char W[], char R[]) {
    int sizeS = strlen(S) + 1;
    int sizeW = strlen(W);
    int sizeR = strlen(R);
    int i, j;
    int pos = 0;
    int replaced = 0;
    char *result = (char *)malloc(sizeof(char) * 1000);

    while (pos != -1) {
        pos = searchWord(S, W);
        if (pos != -1) {
            // 替換單詞
            for (i = 0; i < pos; i++) {
                result[i] = S[i];
            }
            for (j = 0; j < sizeR; j++) {
                result[pos + j] = R[j];
            }
            if (S[pos + sizeW] == ' ' || S[pos + sizeW] == '\0') {
                result[pos + sizeR] = ' ';
                i = pos + sizeW + 1;
            } else {
                result[pos + sizeR] = S[pos + sizeW];
                i = pos + sizeW;
            }
            j = pos + sizeR + 1;
            // 複製剩餘的字元
            while (S[i] != '\0') {
                result[j] = S[i];
                i++;
                j++;
            }
            result[j] = '\0';
            strcpy(S, result);
            replaced = 1;
        }
    }

    if (replaced) {
        printf("%s\n", S);
    }

    free(result);
}

void insertAfterWord(char *sentence, const char *targetWord, const char *insertWord) {
    size_t sentenceLength = strlen(sentence);
    size_t targetLength = strlen(targetWord);
    size_t insertLength = strlen(insertWord);

    size_t i = 0;
    while (i < sentenceLength) {
        if (!isWordCharacter(sentence[i])) {
            i++;
            continue;
        }

        if (strncmp(&sentence[i], targetWord, targetLength) == 0) {
            size_t nextCharIndex = i + targetLength;

            // Check if the word ends
            if (!isWordCharacter(sentence[nextCharIndex])) {
                // Calculate the position to insert the new word
                size_t insertPosition = i + targetLength;

                // Shift the sentence to make space for the new word
                memmove(&sentence[insertPosition + insertLength + 1], &sentence[insertPosition], sentenceLength - insertPosition + 1);

                // Insert the new word at the desired position
                sentence[insertPosition] = ' ';
                memcpy(&sentence[insertPosition + 1], insertWord, insertLength);
                i += targetLength + insertLength + 1;  // Skip past the inserted word and the inserted space
                sentenceLength += insertLength + 1;
            }
        }

        i++;
    }
}

void insertBeforeWord(char *sentence, const char *targetWord, const char *insertWord) {
    size_t sentenceLength = strlen(sentence);
    size_t targetLength = strlen(targetWord);
    size_t insertLength = strlen(insertWord);

    size_t i = 0;
    while (i < sentenceLength) {
        if (!isWordCharacter(sentence[i])) {
            i++;
            continue;
        }

        if (strncmp(&sentence[i], targetWord, targetLength) == 0) {
            size_t nextCharIndex = i + targetLength;

            // Check if the word ends
            if (!isWordCharacter(sentence[nextCharIndex])) {
                // Calculate the position to insert the new word
                size_t insertPosition = i;

                // Shift the sentence to make space for the new word and space
                memmove(&sentence[insertPosition + insertLength + 1], &sentence[insertPosition], sentenceLength - insertPosition + 1);

                // Insert the new word at the desired position
                memcpy(&sentence[insertPosition], insertWord, insertLength);
                sentence[insertPosition + insertLength] = ' ';  // Add space after insertWord
                i += insertLength + 1;  // Skip past the inserted word and the inserted space
                sentenceLength += insertLength + 1;
            }
        }

        i++;
    }
}

void deleteTargetWord(char *sentence, const char *targetWord) {
    size_t sentenceLength = strlen(sentence);
    size_t targetLength = strlen(targetWord);

    size_t i = 0;
    while (i < sentenceLength) {
        if (!isWordCharacter(sentence[i])) {
            i++;
            continue;
        }

        if (strncmp(&sentence[i], targetWord, targetLength) == 0) {
            size_t nextCharIndex = i + targetLength;

            // Check if the word ends
            if (!isWordCharacter(sentence[nextCharIndex])) {
                // Calculate the position to delete the target word
                size_t deletePosition = i;

                // Shift the sentence to remove the target word and following characters
                size_t shiftLength = targetLength;
                while (isWordCharacter(sentence[deletePosition + shiftLength])) {
                    shiftLength++;
                }
                memmove(&sentence[deletePosition], &sentence[deletePosition + shiftLength], sentenceLength - deletePosition - shiftLength + 1);
                sentenceLength -= shiftLength;
            }
        }

        i++;
    }
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

void removeLeadingSpace(char sentence[]) {
    int length = strlen(sentence);
    char* result = (char*)malloc((length + 1) * sizeof(char));

    int i = 0;
    int j = 0;
    
    // 跳過開頭的空白
    while (sentence[i] == ' ') {
        i++;
    }
    
    // 複製剩餘的字元到結果字串中
    while (i < length) {
        result[j] = sentence[i];
        i++;
        j++;
    }
    
    result[j] = '\0'; // 加上結尾字元
    strcpy(sentence, result);
    free(result);
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