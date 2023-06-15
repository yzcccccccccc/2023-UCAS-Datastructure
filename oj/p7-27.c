#include<stdio.h>
#include<stdlib.h>
#define N 10000010

typedef struct Node{
    int v;
    struct Node *next;
}Node;

Node *edge[N];
int n, k, s, t;

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
int Path_Search(int u, int v, int len){
    if (len == k + 1)   return 0;
    if (len == k && u == v) return 1;
    if (vis[u]) return 0;
    vis[u] = 1;
    Node * p = edge[u]->next;
    while (p != NULL){
        if (Path_Search(p->v, v, len + 1))
            return 1;
        p = p->next;
    }
    return 0;
}

int main(){
    scanf("%d,%d", &n, &k);
    Init();
    scanf("%d,%d", &s, &t);
    //printf("%d %d %d %d\n", n, k, s ,t);
    char tmp = 0;
    for (int u, v; tmp != '\n';){
        scanf("%d-%d%c", &u, &v, &tmp);
        InsertEdge(u, v);
    }
    if (Path_Search(s, t, 0))
        printf("yes");
    else
        printf("no");
    return 0;
}