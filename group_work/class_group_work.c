#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void fun(char fileName1[20], char fileName2[20], char C[20], char D[20])
{
    FILE *fp1, *fp2;
    char ch;

    fp1 = fopen(fileName1, "r");
    fp2 = fopen(fileName2, "w");
    if (fp2 == NULL){
        printf("Unable to open file %s\n", fileName2);
        fclose(fp1);
        return;
    }
    int readCount = 0,writeCount = 0,cSize = strlen(C),dSize = strlen(D),found = 0;        
    while ((ch = fgetc(fp1)) != EOF){
        readCount++;
        if (ch == C[0]){//如果開頭跟C開頭一樣
            char buffer[cSize + 1];
            fread(buffer, sizeof(char), cSize, fp1);//讀一個C長度的字串
            readCount += cSize;
            if ((strcmp(buffer, C) == 0) && buffer[cSize] == ' ' || buffer[cSize] == '\0'){//如果buffer等於C
                fputs(D, fp2);
                found = 1;
                writeCount += dSize;
            }
            else{
                fputc(ch, fp2);
                writeCount++;
                fseek(fp1, -cSize, SEEK_CUR);//把fp1移回去(C字串長度)
            }
        }
        else{
            fputc(ch, fp2);
            writeCount++;
        }
    }
    if (!found){
        fputs(D, fp2);
        writeCount += dSize;
    }
    fseek(fp2, 0, SEEK_END);
    long int fileSize = ftell(fp2);
    fclose(fp1);
    fclose(fp2);
    printf("Number of characters read: %d\n", readCount);
    printf("Number of characters written: %d\n", writeCount);
    printf("B file size: %ld bytes\n", fileSize);
}

int main()
{
    char A[20], B[20], C[20], D[20];
    scanf("%s\n%s\n", A, B);
    scanf("%s\n%s\n", C, D);
    fun(A, B, C, D);
    return 0;
}