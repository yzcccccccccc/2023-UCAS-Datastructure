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

int vis[N], max_len;
void Len_Search(int u, int len){
    if (vis[u]) return;
    vis[u] = 1;
    if (len > max_len)  max_len = len;
    Node *p = edge[u]->next;
    while (p != NULL){
        Len_Search(p->v, len + 1);
        p = p->next;
    }
    vis[u] = 0;
    return;
}

int main(){
    scanf("%d", &n);
    Init();
    //printf("%d %d %d %d\n", n, k, s ,t);
    char tmp = 0;
    for (int u, v; tmp != '\n';){
        scanf("%d-%d%c", &u, &v, &tmp);
        InsertEdge(u, v);
    }
    for (int i = 1; i <= n; i++){
        max_len = 0;
        Len_Search(i, 0);
        printf("%d%c", max_len, (i == n ? '\n' : ','));
    }
    return 0;
}