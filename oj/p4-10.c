#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#define LEN 1919810

void reverse(char *p){
    if (*p == '\0') return;
    reverse(p + 1);
    printf("%c", *p);
    return;
}

int main(){
    char line[LEN];
    gets(line);
    reverse(line);
    return 0;
}