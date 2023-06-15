#include<stdio.h>
#define SIZE 1010

int color[SIZE][SIZE], visit[SIZE][SIZE];
int n, m, bx, by, dir;

int inboard(int x, int y){
    return (x >= 0 && x < n && y >= 0 && y < m);
}

void dfs(int x, int y){
    visit[x][y] = 1;
    if (inboard(x + 1, y) && color[x + 1][y] == color[x][y] && !visit[x + 1][y])    dfs(x + 1, y);
    if (inboard(x, y + 1) && color[x][y + 1] == color[x][y] && !visit[x][y + 1])    dfs(x, y + 1);
    if (inboard(x - 1, y) && color[x - 1][y] == color[x][y] && !visit[x - 1][y])    dfs(x - 1, y);
    if (inboard(x, y - 1) && color[x][y - 1] == color[x][y] && !visit[x][y - 1])    dfs(x, y - 1);
    return;
}

int main(){
    scanf("%d %d %d %d %d", &n, &m, &bx, &by, &dir);
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            scanf("%d", &color[i][j]);
    dfs(bx, by);
    for (int i = 0; i < n; i++){
        for (int j = 0; j < m; j++)
            printf("%d", visit[i][j] ? 2 : color[i][j]);
        printf("\n");
    }
    return 0;
}