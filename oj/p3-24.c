#include<stdio.h>

int g(int m, int n){
    if (m == 0 && n >= 0)
        return 0;
    else
        return g(m - 1, 2 * n) + n;
}

int n, m;
int main(){
    scanf("%d,%d", &m, &n);
    printf("%d\n", g(m,n));
    return 0;
}