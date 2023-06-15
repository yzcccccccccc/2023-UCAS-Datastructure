#include<stdio.h>
#include<stdlib.h>
#define LEN 100010

typedef struct Node{
    int val;
    struct Node *next;
}Node;

typedef struct LIST{
    Node *h, *t;
    int len;
}LIST;

LIST list;

void INIT(){
    list.len = 0;
    list.h = list.t = NULL;
    return;
}

void Insert(int v){
    Node *p = (Node *)malloc(sizeof(Node));
    p->next = NULL;
    p->val = v;
    if (list.h == NULL)
        list.h = p;
    else{
        Node *q = list.h;
        while (q->next != NULL) q = q->next;
        q->next = p;
    }
    return;
}

int Query(int v){
    list.t = list.h;
    while (list.t != NULL){
        if (list.t->val == v)   return 1;
        list.t = list.t->next;
    }
    return 0;
}

int main(){
    INIT();
    int val;
    char ctr = '\0';
    while (ctr != '\n'){
        scanf("%d%c", &val, &ctr);
        Insert(val);
    }
    ctr = '\0';
    while (ctr != '\n'){
        scanf("%d%c", &val, &ctr);
        printf("%d%c", Query(val), ctr);
    }
    return 0;
}