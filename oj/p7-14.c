#include<stdio.h>
#include<stdlib.h>
#define N 10000010

typedef struct Node{
    int v;
    struct Node *next;
}Node;

Node *edge[N];
int n, m;

void Init(){
    Node *p;
    for (int i = 0; i <= n; i++){
        p = (Node *)malloc(sizeof(Node));
        p->next = NULL;
        edge[i] = p;
    }
    return;
}

// add an edge from u to v
void InsertEdge(int u, int v){
    Node *q = edge[u];
    Node *p = (Node *)malloc(sizeof(Node));
    p->v = v;
    p->next = NULL;
    while (q->next != NULL && q->next->v > v)  q = q->next;
    p->next = q->next;
    q->next = p;
    return;
}

void Print(int node){
    Node *p = edge[node]->next;
    if (p != NULL){
        printf(" ");
        while (p != NULL){
            printf("%d", p->v);
            if (p->next != NULL)    printf(",");
            p = p->next;
        }
    }
    return;
}

int main(){
    scanf("%d,%d", &n, &m);
    Init();
    int zero_mark = 0;
    for (int i = 0, u, v; i < m; i++){
        char tmp;
        scanf("%d-%d%c", &u, &v, &tmp);
        if (u == 0 || v == 0)   zero_mark = 1;
        InsertEdge(u, v);
    }
    if (!zero_mark)
        for (int i = 1; i <= n; i++){
            printf("%d", i);
            Print(i);
            if (i != n)
                printf("\n");
        }
    else
        for (int i = 0; i < n; i++){
            printf("%d", i);
            Print(i);
            if (i != n - 1)
                printf("\n");
        }
    return 0;
}