#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    FILE* file = fopen("test.c", "r");
    if (file == NULL) {
        printf("Unable to open file.\n");
        return 1;
    }

    // 逐行讀取檔案內容
    char line[100];
    while (fgets(line, sizeof(line), file) != NULL) {
        // 檢查是否為變數宣告的行
        if (strstr(line, "int ") != NULL || strstr(line, "char ") != NULL) {
            // 分析變數資料型別和變數名稱
            char* typeStart = strstr(line, "int ") != NULL ? strstr(line, "int ") : NULL;
            if (typeStart == NULL)
                typeStart = strstr(line, "char ") != NULL ? strstr(line, "char ") : NULL;

            if (typeStart != NULL) {
                // 找到變數名稱的起始位置
                char* varNameStart = typeStart + strlen(typeStart);
                while (*varNameStart == ' ') {
                    varNameStart++;
                }
                // 找到變數名稱的結束位置
                char* varNameEnd = varNameStart;
                while (*varNameEnd != ';' && *varNameEnd != ',' && *varNameEnd != ' ' && *varNameEnd != '\n') {
                    varNameEnd++;
                }
                // 輸出變數資料型別和變數名稱
                int varNameLength = varNameEnd - varNameStart;
                char varName[varNameLength + 1];
                strncpy(varName, varNameStart, varNameLength);
                varName[varNameLength] = '\0';
                printf("type:%.*s,name:%s\n", (int)(typeStart - line), line, varName);
            }
        }
    }
    fclose(file);
    return 0;
}
