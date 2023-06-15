#include<stdio.h>
#include<string.h>
#include<stdlib.h>

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

void check(){
    Node *s, *t;
    s = str->h->next;
    t = str->t;
    while (s != t){
        if (s->data != t->data){
            printf("0\n");
            return;
        }
        s = s->next;
        t = t->pre;
    }
    printf("1\n");
    return;
}

int main(){
    scanf("%d\n", &n);
    str = Init(n);
    for (int i = 0, c; i < n; i++){
        scanf("%c", &c);
        Insert(c);
    }
    //print();
    check();
    return 0;
}