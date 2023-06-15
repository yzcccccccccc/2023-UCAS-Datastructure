#include<stdio.h>
#include<stdlib.h>
#define N 10000010

typedef struct Node{
    int v;
    struct Node *next;
}Node;

Node *edge[N];
int n;

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

int vis[N];
void search(int u){
    if (vis[u]) return;
    vis[u] = 1;
    Node *p = edge[u]->next;
    while (p != NULL){
        search(p->v);
        p = p->next;
    }
    return;
}

int main(){
    scanf("%d", &n);
    Init();
    int u, v;
    char tmp, opr;
    tmp = '\n';
    do{
        scanf("%d%c%d%c", &u, &opr, &v, &tmp);
        if (opr == ',') break;
        InsertEdge(u, v);
    }while (tmp != '\n');
    if (opr != ',')
        scanf("%d,%d", &u, &v);
    search(u);
    if (vis[v])
        printf("yes");
    else
        printf("no");
    return 0;
}