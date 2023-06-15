#include<stdio.h>
#define MAXLEN 10010

int v[MAXLEN], c[MAXLEN], len;

int main(){
    int val;
    while (scanf("%d", &val) != EOF){
        v[len] = val;
        len++;
    }
    for (int i = 0; i < len; i++)
        for (int j = 0; j < len; j++)
            c[i] += (v[j] < v[i]);
    for (int i = 0; i < len; i++){
        printf("%d", c[i]);
        if (i != len - 1)   printf(" ");
    }
    return 0;
}