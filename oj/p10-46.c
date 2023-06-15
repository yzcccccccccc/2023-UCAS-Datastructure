#include<stdio.h>
#define MAXLEN 10010
#define INF 1e9 + 7

int val[MAXLEN], n;
int res[MAXLEN];

int main(){
    scanf("%d", &n);
    for (int i = 0; i < n; i++) scanf("%d", &val[i]);
    for (int i = 0; i < n; i++){
        int min = INF, pos = -1;
        for (int j = 0; j < n; j++)
            if (val[j] < min){
                min = val[j];
                pos = j;
            }
        res[i] = min;
        val[pos] = INF;
    }
    for (int i = 0; i < n; i++){
        printf("%d", res[i]);
        if (i != n - 1) printf(" ");
    }
    return 0;
}