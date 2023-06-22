#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int findNextEnd(char *s)
{
    int n = 0;
    while ((s[n] != ' ') || (s[n] == '\0'))
    {
        n++;
    }
    return n;
}

int isBeInsertedWord(char *s, char *b)
{
    int n = strlen(b);
    if ((strncmp(s, b, n) == 0) && ((s[n] == ' ') || (s[n] == '\0')))
        return 1;
    else
        return 0;
}

char **replace(char *s, char *beInsertedWord, char *insertingWord, int *count)
{
    int i = 0, index = 0, nextEnd = 0;
    int lenB = strlen(beInsertedWord);
    char **r = NULL;
    r = (char **)malloc(100 * sizeof(void *));
    int len = strlen(s);
    while (i < len)
    {
        if (isBeInsertedWord(&s[i], beInsertedWord) == 1)
        {
            r[index++] = beInsertedWord;
            s[i + lenB] = '\0';
            i = i + 1;
        }
        else
        {
            r[index++] = &s[i];
            nextEnd = findNextEnd(&s[i]);
            i = i + nextEnd;
            s[i++] = '\0';
        }
    }
    (*count) = index;
    return r;
}

char **insertWord(char *s, char *beInsertedWord, char *insertingWord, int *count)
{
    int i = 0, index = 0, nextEnd = 0;
    int lenB = strlen(beInsertedWord);
    char **r = NULL;
    r = (char **)malloc(100 * sizeof(void *));
    int len = strlen(s);
    while (i < len)
    {
        if (isBeInsertedWord(&s[i], beInsertedWord) == 1)
        {
            r[index++] = insertingWord;
            r[index++] = beInsertedWord;
            s[i + lenB] = '\0';
            i = i + lenB + 1;
        }
        else
        {
            r[index++] = &s[i];
            nextEnd = findNextEnd(&s[i]);
            i = i + nextEnd;
            s[i++] = '\0';
        }
    }
    (*count) = index;
    return r;
}

char **insert_behind(char *s, char *beInsertedWord, char *insertingWord, int *count)
{
    int i = 0, index = 0, nextEnd = 0;
    int lenB = strlen(beInsertedWord);
    char **r = NULL;
    r = (char **)malloc(100 * sizeof(void *));
    int len = strlen(s);
    while (i < len)
    {
        if (isBeInsertedWord(&s[i], beInsertedWord) == 1)
        {
            r[index++] = insertingWord;
            r[index++] = beInsertedWord;
            s[i + lenB] = '\0';
            i = i + lenB + 1;
        }
        else
        {
            r[index++] = &s[i];
            nextEnd = findNextEnd(&s[i]);
            i = i + nextEnd;
            s[i++] = '\0';
        }
    }
    (*count) = index;
    return r;
}

void f4()
{
    char str[100]; char A[100];
    char P[20];
    char Q[20];
    char **p = NULL;
    int n = 0, j = 0;
    gets(str); gets(P); gets(Q);
    strcpy(A, str);
    for(int i = 0; i < 100; i++){
        printf("%s ", A[i]);
    }
    p = replace(A, P, Q, &n);
    for (j = 0; j < n; j++)
    {
        printf("%s ", p[j]);
    }

    n = 0;strcpy(str, A);
    p = insertWord(A, P, Q, &n);
    for (j = 0; j < n; j++)
    {
        printf("%s ", p[j]);
    }

    n = 0;strcpy(str, A);
    p = insert_behind(A, P, Q, &n);
    for (j = 0; j < n; j++)
    {
        printf("%s ", p[j]);
    }
}

int main()
{
    f4();
    return 0;
}