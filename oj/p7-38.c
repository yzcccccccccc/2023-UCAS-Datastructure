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
    //while (q->next != NULL && q->next->v > v)  q = q->next;
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

char ELEM[N];
void Print_Tree(int u){
    Node *p = edge[u]->next;
    while (p != NULL){
        Print_Tree(p->v);
        p = p->next;
    }
    printf("%c", ELEM[u]);
    return;
}

int main(){
    scanf("%d", &n);
    Init();
    //printf("%d %d %d %d\n", n, k, s ,t);
    char elem, ope;
    scanf("%c", &ope);
    for (int u1, u2, i = 0; i < n; i++){
        scanf("%c%c", &elem, &ope);
        ELEM[i] = elem;
        if (ope != '\n'){
            scanf("%d%d%c", &u1, &u2, &ope);
            InsertEdge(i, u1);
            InsertEdge(i, u2);
        }
    }
    Print_Tree(0);
    return 0;
}