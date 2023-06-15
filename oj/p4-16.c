#include<stdio.h>
#include<string.h>
#define LEN 1919810

char s[LEN], t[LEN];

int mycmp(char *p, char *q){
    while (*p == *q && *p != '\0' && *q != '\0'){
        p++;
        q++;
    }
    if (*p == '\0' && *q == '\0')
        return 0;
    return *p > *q ? 1 : -1;
}

int main(){
    scanf("%s%s", s, t);
    printf("%d\n", mycmp(s, t));
    return 0;
}