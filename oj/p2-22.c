#include<stdio.h>
#include<string.h>
#include<stdlib.h>

typedef char ElemType;
typedef int Status;

typedef struct node{
    ElemType data;
    struct node *next;
}Link;

Link *list;

Link *Init(){
    Link *h = (Link *)malloc(sizeof(Link));
    //h: head node (store info)
    h->data = 0;
    h->next = NULL;
    return h;
}

Status Insert(Link *h, ElemType val){
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

Status Delete_range(Link *h, ElemType minn, ElemType maxx){
    Link *p = h;
    Link *tmp;
    while (p->next != NULL){
        if (minn < p->next->data && p->next->data < maxx){
            tmp = p->next;
            p->next = p->next->next;
            free(tmp);
        }
        else
            p = p->next;
    }
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

void Print_reverse(Link *p){
    if (p == NULL)  return;
    Print_reverse(p->next);
    if (p != list){
        printf("%c", p->data);
        if (p != list->next)
            printf(",");
    }
    return;
}


int main(){
    list = Init();
    char c = getchar(), c1;
    while (c != '\n'){
        if (c == ','){
            Insert(list, c1);
        }
        c1 = c;
        c = getchar();
    }
    Insert(list, c1);
    Print_reverse(list);
    return 0;
}