#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#define inf 1919810

typedef int ElemType;
typedef int Status;

typedef struct Node{
    ElemType val;
    int freq, seq;
    struct Node *next, *prior;
}Link;

Link *Init(){
    Link *h = (Link *)malloc(sizeof(Link));
    //h is a head node
    h->freq = h->val = 0;
    h->prior = h->next = h;
    return h;
}

Status Insert(ElemType val, int freq, Link *list){
    Link *p = (Link *)malloc(sizeof(Link)), *h = list->next;
    if (!p) return 0;
    p->val = val;
    p->freq = freq;
    p->seq = inf;
    while (h->next != list){
        h = h->next;
    }
    p->prior = h;
    p->next = list;
    h->next = p;
    list->prior = p;
    return 1;
}

//adjust node p
Status Adjust(Link *p, Link *list){
    p->prior->next = p->next;
    p->next->prior = p->prior;
    Link *h = list->next;
    while (h != list){
        if (h->freq < p->freq || h->freq == p->freq && h->seq > p->seq){
            h->prior->next = p;
            p->prior = h->prior;
            h->prior = p;
            p->next = h;
            break;
        }
        h = h->next;
    }
    if (h == list){
        h->prior->next = p;
        p->prior = h->prior;
        h->prior = p;
        p->next = h;    
    }
    return 1;
}

Status Locate(ElemType val, Link *list, int seq){
    Link *p = list->next;
    while (p != list){
        if (p->val == val){
            p->freq++;
            p->seq = (seq < p->seq) ? seq : p->seq;
            Adjust(p, list);
        }
        p = p->next;
    }
    return 1;
}

Status Print(Link *list){
    if (list == NULL)   return 0;
    Link *p = list->next;
    while (p != list){
        printf("%d ", p->val);
        p = p->next;
    }
    printf("\n");
    return 1;
}

int n, v;
int main(){
    Link *list = Init();
    scanf("%d", &n);
    for (int i = 0; i < n; i++){
        scanf("%d", &v);
        Insert(v, 0, list);
    }
    int index = 0;
    while (scanf("%d", &v) != EOF){
        Locate(v, list, index++);
        //Print(list);
    }
    Print(list);
    return 0;
}