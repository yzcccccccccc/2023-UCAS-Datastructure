#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#define LEN 1919810
#define inf 1919810
#define min(a, b) (a < b ? a : b)
char s[LEN], t[LEN], r[LEN];
int mark[255], ls, lt, lr;
int main(){
    for (int i = 0; i < 256; i++)   mark[i] = inf;
    scanf("%s%s", s, t);
    ls = strlen(s);
    lt = strlen(t);
    for (int i = 0; i < ls; i++){
        mark[s[i]] = min(i + 1, mark[s[i]]);
    }
    for (int i = 0; i < lt; i++)
        mark[t[i]] = 0;
    for (int i = 0; i < ls; i++)
        if (mark[s[i]] == i + 1)
            r[lr++] = s[i];
    r[lr] = '\0';
    if (lr != 0){
        printf("%s ", r);
        for (int i = 0; i < lr; i++)
            printf("%d", mark[r[i]] - 1);
    }
    else
        printf("-1");
    return 0;
}