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
    while (cur->next != NULL)    cur = cur->next;
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

void SelectSort(){
    Node *p = list->next;
    while (p != NULL){
        int min = INF;
        Node *pos, *cur;
        cur = p;
        while (cur != NULL){
            if (cur->val < min){
                min = cur->val;
                pos = cur;
            }
            cur = cur->next;
        }
        int tmp = p->val;
        p->val = min;
        pos->val = tmp;
        p = p->next;
    }
    return;
}

int main(){
    Init();
    int v;
    while (scanf("%d", &v) != EOF) Insert(v);   
    SelectSort();
    Print();
    return 0;
}