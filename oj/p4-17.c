#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#define LEN 1919810

typedef int Status;

typedef struct Node{
    char data;
    struct Node *next, *pre;
}Node;

typedef struct String{
    Node *h, *t;
    int len;
}String;

String *str;
int n;

String *Init(int len){
    String *tmp_str = (String *)malloc(sizeof(String));
    Node *tmp_node = (Node *)malloc(sizeof(Node));

    tmp_node->next = tmp_node->pre = tmp_node;

    tmp_str->len = len;
    tmp_str->h = tmp_str->t = tmp_node;
    return tmp_str;
}

Status Insert(char c){
    Node *p = (Node *)malloc(sizeof(Node));
    p->data = c;

    p->next = str->h;
    p->pre = str->t;
    str->t->next = p;
    str->h->pre = p;

    str->t = p;
    return 1;
}

Status print(){
    Node *p = str->h->next;
    while (p != str->h){
        printf("%c", p->data);
        p = p->next;
    }
    printf("\n");
    return 1;
}

Node *LookUp(Node *start, char *target){
    Node *p = start, *tmp;
    char *t = target;
    while (p != str->h){
        if (p->data == *t){
            tmp = p;
            while (tmp->data == *t && *t != '\0'){
                tmp = tmp->next;
                t++;
            }
            if (*t == '\0'){
                return p;
            }
        }   
        t = target;
        p = p->next;
    }
    return NULL;
}

void Replace(char *t, char *v){
    Node *p = str->h->next, *q, *tmp;
    int lt = strlen(t);
    int lv = strlen(v);
    p = LookUp(p, t);
    while (p != NULL){
        q = p;
        p = p->pre;
        for (int i = 0; i < lt; i++){
            q = q->next;
            free(q->pre);
        }
        for (int i = 0; i < lv; i++, p = p->next){
            tmp = (Node *)malloc(sizeof(Node));
            tmp->data = v[i];
            tmp->next = q;
            tmp->pre = p;
            p->next = tmp;
        }
        q->pre = tmp;
        //print();
        p = LookUp(q, t);
    }
    return;
}

char S[LEN], T[LEN], V[LEN];
int main(){
    scanf("%s%s%s", S, T, V);
    int ls = strlen(S);
    str = Init(ls);
    for (int i = 0; i < ls; i++){
        Insert(S[i]);
    }
    //LookUp(str->h->next, T);
    Replace(T, V);
    print();
    return 0;
}