#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#define HEAD_MARK -114514

typedef int ElemType;
typedef int Status;

typedef struct QNode{
    ElemType val;
    struct QNode *next;
}QNode;

typedef struct Queue{
    QNode *tail;
}Queue;

Queue *Init(){
    Queue *p = (Queue *)malloc(sizeof(Queue));
    QNode *q = (QNode *)malloc(sizeof(QNode));
    //q: the head node.
    q->next = q;
    q->val = HEAD_MARK;
    p->tail = q;
    return p;
}

Status Insert(Queue *que, ElemType val){
    QNode *p = que->tail, *q;
    q = (QNode *)malloc(sizeof(QNode));
    if (!q) return 0;
    q->val = val;
    q->next = p->next;
    p->next = q;
    que->tail = q;
    return 1;
}

Status Print(Queue *que){
    QNode *p = que->tail->next, *q;
    q = p->next;
    while (q != p){
        printf("%d", q->val);
        if (q->next != p)
            printf(",");
        q = q->next;
    }
    return 1;
}

int main(){
    Queue *que = Init();
    int n, v;
    scanf("%d", &n);
    for (int i = 0; i < n; i++){
        scanf("%d", &v);
        if (i < n - 1)  scanf(",");
        Insert(que, v);
    }
    Print(que);
    return 0;
}