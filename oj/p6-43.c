#include<stdio.h>
#include<string.h>
#define N 10000010

int L[N], R[N], len;
int u, v;

void dfs(int node){
    if (node == 0)  return;
    dfs(L[node]);
    dfs(R[node]);
    int tmp = L[node];
    L[node] = R[node];
    R[node] = tmp;
    return;
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
    dfs(1);
    for (int i = 0; i < len; i++)
        printf("%d%c", L[i], (i == len - 1 ? '\n' : ' '));
    for (int i = 0; i < len; i++)
        printf("%d%c", R[i], (i == len - 1 ? '\n' : ' '));
    return 0;
}