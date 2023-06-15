#include<stdio.h>
#include<string.h>
#include<stdlib.h>

typedef int ElemType;
typedef int Status;

typedef struct node{
    ElemType data;
    struct node *next;
}Link;


Link *Init(){
    Link *h = (Link *)malloc(sizeof(Link));
    //h: head node (store info)
    h->data = 0;
    h->next = NULL;
    return h;
}

Status Insert(Link *h, ElemType val){
    //printf("%d\n", val);
    Link *p = (Link *)malloc(sizeof(Link));
    if (!p) return 0;
    Link *q = h;
    while (q->next != NULL) q = q->next;
    p->data = val;
    p->next = NULL;
    q->next = p;
    h->data++;
    return 1;
}

Status Delete(Link *h, int pos){
    Link *p = h;
    if (pos > h->data) return 0;
    int index = 0;
    while (index < pos){
        p = p->next;
        index++;
    }
    Link *tmp = p->next;
    p->next = p->next->next;
    free(tmp);
    h->data--;
    return 1;
}

Status Print(Link *h){
    if (h->data == 0)
        printf("NULL");
    else{
        Link *p = h->next;
        while (p != NULL){
            printf("%d ", p->data);
            p = p->next;
        }
    }
    printf("\n");
    return 1;
}

int main(){
    Link *list = Init();
    int n;
    ElemType v = 0;
    while (1){
        scanf("%d", &v);
        //printf("%d\n", v);
        Insert(list, v);
        if (getchar() == '\n')
            break;
    }
    //Print(list);
    scanf("%d", &n);
    Delete(list, n);
    Print(list);
    return 0;
}