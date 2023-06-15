#include<stdio.h>
#include<string.h>
#define MAXN 1010
int map[MAXN][MAXN];
int n, m;

typedef struct Point{
    int x, y;
}Point;

Point Entra, Exit, Key;

Point queue[MAXN * MAXN];
int pre_point[MAXN * MAXN];
int vis[MAXN][MAXN];
int mx[4] = {0, 0, 1, -1};
int my[4] = {1, -1, 0, 0};
int h, t;

int inBox(int x, int y){
    return x >= 0 && x < n && y >= 0 && y < m;
}

int printed;
void Print(int pos){
    if (pre_point[pos] == -1) return;
    Print(pre_point[pos]);
    printf("\n");
    printf("%d %d", queue[pos].x + 1, queue[pos].y + 1);
    return;
}

void BFS(Point Start, Point End){
    h = t = 0;
    memset(vis, 0, sizeof(vis));

    queue[t] = Start;
    vis[Start.x][Start.y] = 1;
    pre_point[t] = -1;
    t++;

    Point cur, insert;
    while (h < t){
        cur = queue[h];
        if (cur.x == End.x && cur.y == End.y)
            break;
        for (int i = 0; i < 4; i++){
            insert.x = cur.x + mx[i];
            insert.y = cur.y + my[i];
            if (inBox(insert.x, insert.y) && !vis[insert.x][insert.y] && !map[insert.x][insert.y]){
                vis[insert.x][insert.y] = 1;
                queue[t] = insert;
                pre_point[t] = h;
                t++;
            }
        }
        h++;
    }
    Print(h);
    return;
}

int main(){
    scanf("%d%d", &n, &m);
    char ctr;
    for (int i = 0; i < n; i++){
        scanf("%c", &ctr);
        for (int j = 0; j < m; j++){
            scanf("%c", &ctr);
            if (ctr == '1') 
                map[i][j] = 1;
            else
                map[i][j] = 0;
            if (ctr == 'R'){
                Entra.x = i;
                Entra.y = j;
            }
            if (ctr == 'Y'){
                Key.x = i;
                Key.y = j;
            }
            if (ctr == 'C'){
                Exit.x = i;
                Exit.y = j;
            }
        }
    }
    printf("%d %d", Entra.x + 1, Entra.y + 1);
    BFS(Entra, Key);
    BFS(Key, Exit);
    return 0;
}