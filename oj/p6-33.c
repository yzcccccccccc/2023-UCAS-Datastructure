#include<stdio.h>
#include<string.h>
#define N 10000010

int L[N], R[N], len;
int u, v;

int dfs(int node){
    if (node == 0) return 0;
    if (node == u)  return 1;
    return dfs(L[node]) || dfs(R[node]);
}

int main(){
    int x;
    char c;
    len = 0;
    while (scanf("%d%c", &x, &c) == 2){
        L[len] = x;
        len++;
        if (c == '\n')  break;
    }
    len = 0;
    while (scanf("%d%c", &x, &c) == 2){
        R[len] = x;
        len++;
        if (c == '\n')  break;
    }
    scanf("%d%d", &u, &v);
    if (u == v)
        printf("0");
    else
        printf("%d", dfs(v));
    return 0;
}