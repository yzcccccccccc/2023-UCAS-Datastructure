#include<stdio.h>
#define SIZE 1010

int coe[SIZE][SIZE];
int n, m;

int main(){
    scanf("%d%d", &n, &m);
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            scanf("%d", &coe[i][j]);
    for (int i = n - 1; i >= 0; i--)
        for (int j = m - 1; j >= 0; j--){
            if (coe[i][j] == 0)
                continue;
            if (coe[i][j] != 1 || i == 0 && j ==0)
                printf("%d", coe[i][j]);
            if (i > 0)
                printf("xE%d", i);
            if (j > 0)
                printf("yE%d", j);
            if (i > 0 || j > 0)
                printf("+");
        }
    return 0;
}