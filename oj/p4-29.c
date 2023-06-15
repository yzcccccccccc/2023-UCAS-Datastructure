#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#define LEN 10000010

int next[LEN], sl, pl;
char s[LEN], p[LEN];

void getNext(){
    next[0] = -1;
    int i = 0;
    int k = -1;
    while (i < pl - 1){
        if (k == -1 || p[i] == p[k]){
            i++;
            k++;
            next[i] = k;
        }
        else
            k = next[k];
    }
    return;
}

int Kmp(){
    int i = 0;
    int j = 0;
    while (i < sl && j < pl){
        if (j == -1 || s[i] == p[j]){
            i++;
            j++;
        }
        else
            j = next[j];
    }
    if (j == pl){
        return i - j;
    }
    else
        return -1;
}

int main(){
    scanf("%d %d\n", &sl, &pl);
    for (int i = 0; i < sl; i++)    scanf("%c", &s[i]);
    scanf("\n");
    for (int i = 0; i < pl; i++)    scanf("%c", &p[i]);
    getNext();
    printf("%d\n", Kmp());
    return 0;
}