#include<stdio.h>
#define N 10000010

int n;
int s[2 * N], fst[N], lst[N];
int vis[N];

int Loop_Search(int u){
    if (vis[u]) return 1;
    vis[u] = 1;
    for (int i = fst[u]; i < lst[u]; i++)
        if (Loop_Search(s[i]))
            return 1;
    vis[u] = 0;
    return 0;
}

int main(){
    char tmp;
    scanf("%d%c", &n, &tmp);
    tmp = 0;
    for (int i = 0; tmp != '\n'; i++){
        scanf("%d%c", &s[i], &tmp);
    }
    for (int i = 0; i <= n; i++)
        scanf("%d", &fst[i]);
    for (int i = 0; i <= n; i++)
        scanf("%d", &lst[i]);
    for (int i = 1; i <= n; i++)
        if (!vis[i]){
            if (Loop_Search(i)){
                printf("yes");
                return 0;
            }
        }
    printf("no");
    return 0;
}