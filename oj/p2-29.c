#include<stdio.h>
#include<string.h>
#include<stdlib.h>

typedef char ElemType;
typedef int Status;

typedef struct node{
    ElemType data;
    struct node *next;
}Link;

Link *lista, *listb, *listc;

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

//delete p->next
Status Delete_next(Link *p){
    Link *tmp = p->next;
    if (p == NULL)  return 0;
    p->next = p->next->next;
    free(tmp);
    return 1;
}

Status Query(Link *list, ElemType val){
    Link *p = list;
    while (p->next != NULL){
        if (p->next->data == val)
            return 1;
        else
            p = p->next;
    }
    return 0;
}

Status process(){
    Link *p = lista;
    while (p->next != NULL){
        if (Query(listb, p->next->data) && Query(listc, p->next->data))
            Delete_next(p);
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
            printf("%c", p->data);
            if (p->next != NULL)
                printf(",");
            p = p->next;
        }
    }
    printf("\n");
    return 1;
}

Status input_list(Link *list){
    char c = getchar(), c1;
    while (c != '\n'){
        if (c == ','){
            Insert(list, c1);
        }
        c1 = c;
        c = getchar();
    }
    Insert(list, c1);
    return 1;
}


int main(){
    lista = Init();
    listb = Init();
    listc = Init();
    
    input_list(lista);
    input_list(listb);
    input_list(listc);

    process();

    Print(lista);

    return 0;
}