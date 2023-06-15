#include<stdio.h>
#define SIZE 1010

int val[SIZE * SIZE], l;
int mat[SIZE][SIZE];
int m, n;

void getV(){
    char c = getchar();
    int rt = 0;
    int sign = 1;

    l = 0;
    while ((c = getchar()) != '\n'){
        if (c == '-'){
            sign = -1;
            continue;
        }
        if (c >= '0' && c <= '9'){
            rt = rt * 10 + c - '0';
        }
        if (c == ' '){
            val[l] = sign * rt;
            rt = 0;
            sign = 1;
            l++;
        }
    }
    val[l] = rt * sign;
    //for (int i = 0; i <= l; i++)    printf("%d ", val[i]);
    //printf("\n");
    return;
}

int main(){
    scanf("%d%d", &m, &n);
    getV();
    l = 0;
    for (int i = 0, v; i < m; i++){
        for (int j = 0; j < n; j++){
            scanf("%d", &v);
            if (v)
                mat[i][j] = val[l++];
        }
    }
    getV();
    l = 0;
    for (int i = 0, v; i < m; i++){
        for (int j = 0; j < n; j++){
            scanf("%d", &v);
            if (v)
                mat[i][j] += val[l++];
        }
    }
    l = 0;
    for (int i = 0; i < m; i++){
        for (int j = 0; j < n; j++)
            if (mat[i][j])
                val[l++] = mat[i][j];
    }
    for (int i = 0; i < l; i++)
        printf("%d%c", val[i], (i == l - 1) ? '\n' : ' ');
    if (l == 0)
        printf("\n");
    for (int i = 0; i < m; i++)
        for (int j = 0; j < n; j++){
            printf("%d", mat[i][j] ? 1 : 0);
            printf("%c", (j == n - 1) ? '\n' : ' ');
        }
    return 0;
}