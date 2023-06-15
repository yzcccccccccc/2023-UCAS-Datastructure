#include<stdio.h>
#include<stdlib.h>
#define INF 1e9 + 7

typedef struct Node{
    int val;
    struct Node *next;
}Node;

Node *list;

void Init(){
    list = (Node *)malloc(sizeof(Node));
    list->next = NULL;
    list->val = -INF;
    return;
}

void Insert(int v){
    Node *p = (Node *)malloc(sizeof(Node));
    p->next = NULL;
    p->val = v;

    Node *cur = list;
    while (cur->next != NULL && cur->next->val <= v)    cur = cur->next;
    p->next = cur->next;
    cur->next = p;
    return;
}

void Print(){
    Node *p = list->next;
    int printed = 0;
    while (p != NULL){
        if (printed) printf(" ");
        printed = 1;
        printf("%d", p->val);
        p = p->next;
    }
    return;
}

int main(){
    Init();
    int n, v;
    scanf("%d", &n);
    for (int i = 0; i < n; i++){
        scanf("%d", &v);
        Insert(v);
    }    
    Print();
    return 0;
}