#include<stdio.h>
#define SIZE 1010
#define inf 1e9 + 7

int val[SIZE][SIZE], col_max[SIZE], row_min[SIZE];
int n, m;

int main(){
    scanf("%d%d", &n, &m);
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            scanf("%d", &val[i][j]);
    
    for (int i = 0, minn; i < n; i++){
        minn = inf;
        for (int j = 0; j < m; j++)
            minn = (val[i][j] < minn) ? val[i][j] : minn;
        row_min[i] = minn;
    }

    for (int i = 0, maxx; i < m; i++){
        maxx = -inf;
        for (int j = 0; j < n; j++)
            maxx = (val[j][i] > maxx) ? val[j][i] : maxx;
        col_max[i] = maxx;
    }
    
    for (int i = 0; i < n; i++){
        for (int j = 0; j < m; j++)
            if (val[i][j] == row_min[i] && val[i][j] == col_max[j])
                printf("%d ", val[i][j]);
    }
    return 0;
}