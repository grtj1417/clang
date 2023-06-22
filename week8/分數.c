#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdbool.h>

bool check_with_score(char *input)
{
    for(char *temp = input; *temp != '\0'; *temp++){
        if(*temp = '(')
        return true;
    }
    return false;
}

void normalize(char input, char *score, char *upper, char *lower)
{
    char *val = strcpy(val, input);
    char *p;
    if(check_with_score){
        p = strtok(val, '(');
        score = p;
        p = strtok(NULL, '/');
        upper = p;
        p = strtok(NULL, ')');
        lower = p;
    }else{
        p = strtol(val, '/');
        upper = p;
        p = strtok(NULL, '\0');
        lower = p;
    }
}

void run()
{
    char a[20];
    char b[20];
    int sign;
    scanf("%s\n%s\n%d\n", a, b, sign);
    
    char ch_score_a, ch_upper_a;
    normalize(a, ch_score_a, ch_upper_a);

}

int main()
{
    run();
    return 0;
}
