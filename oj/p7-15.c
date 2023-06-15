#include<stdio.h>
#include<stdlib.h>
#define N 1010
typedef struct Graph{
    int arc[N][N];
    int n;
}Graph;

void Init(Graph *G, int n){
    G->n = n;
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            G->arc[i][j] = 0;
    return;
}

void Load(Graph *G){
    int n = G->n;
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            scanf("%d", &G->arc[i][j]);
    scanf("\n");
    return;
}

void Del_Arc(int u, int v, Graph *G){
    G->arc[u][v] = G->arc[v][u] = 0;
    return;
}

void Ins_Arc(int u, int v, Graph *G){
    G->arc[u][v] = G->arc[v][u] = 1;
    return;
}

void Del_Verx(int u, Graph *G){
    int n = G->n;
    for (int i = u; i < n - 1; i++)
        for (int j = 0; j < n; j++)
            G->arc[i][j] = G->arc[i + 1][j];
    for (int i = 0; i < n - 1; i++)
        for (int j = u; j < n - 1; j++)
            G->arc[i][j] = G->arc[i][j + 1];
    G->n--;
    return;
}

void Ins_Verx(int u, Graph *G){
    int n = G->n;
    for (int i = n; i >= u + 1; i--)
        for (int j = 0; j < n; j++)
            G->arc[i][j] = G->arc[i - 1][j];
    for (int j = n; j >= u + 1; j--)
        for (int i = 0; i <= n; i++)
            G->arc[i][j] = G->arc[i][j - 1];
    for (int i = 0; i <= n; i++)
        G->arc[i][u] = G->arc[u][i] = 0;
    G->n++;
    return;
}

void Print(Graph *G){
    int n = G->n;
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            printf("%d%c", G->arc[i][j], (j == n - 1 ? '\n' : ' '));
    return;
}

int main(){
    Graph *G;
    G = (Graph *)malloc(sizeof(Graph));
    int n;
    scanf("%d", &n);
    Init(G, n);
    Load(G);
    char op1, op2, tmp;
    int u, v;
    while (scanf("%c%c", &op1, &op2) != EOF){
        //printf("%c %c\n", op1, op2);
        if (op2 == 'A'){
            scanf("%d%d%c", &u, &v, &tmp);
            if (op1 == 'D')
                Del_Arc(u, v, G);
            else
                Ins_Arc(u, v, G);
        }
        else{
            scanf("%d%c", &u, &tmp);
            if (op1 == 'D')
                Del_Verx(u, G);
            else
                Ins_Verx(u, G);
        }
    }
    Print(G);
    return 0;
}