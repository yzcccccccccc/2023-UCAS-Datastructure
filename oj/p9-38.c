#include<stdio.h>
#include<stdlib.h>

typedef struct Node{
    int val;
    struct Node *lc, *rc;
}Node;

Node *root[2];

Node *New(){
    Node *p = (Node *)malloc(sizeof(Node));
    p->lc = p->rc = NULL;
    return p;
}

void Init(){
    root[0] = New();
    root[1] = New();
    return;
}

int mark;
int Insert(Node *p){
    if (mark)   return 1;
    int v;  char ctr = '\0';
    scanf("%d%c", &v, &ctr);
    if (ctr == '\n'){
        mark = 1;
    }
    if (v == -1)    return 0;
    p->lc = p->rc = NULL;
    p->val = v;
    p->lc = New();
    if (!Insert(p->lc)){
        free(p->lc);
        p->lc = NULL;
    }
    p->rc = New();
    if (!Insert(p->rc)){
        free(p->rc);
        p->rc = NULL;
    }
    return 1;
}

int printed;
void Print(Node *p){
    if (p == NULL)  return;
    Print(p->lc);
    if (printed)
        printf(" ");
    printed = 1;
    printf("%d", p->val);
    Print(p->rc);
    return;
}

void Merge(int v){
    Node *p, *par;
    p = par = root[0];
    while (p != NULL){
        par = p;
        if (v < p->val)
            p = p->lc;
        else
            p = p->rc;
    }
    if (v < par->val){
        par->lc = New();
        par->lc->val = v;
    }
    else{
        par->rc = New();
        par->rc->val = v;
    }
    return;
}

int main(){
    Init();
    mark = 0;
    Insert(root[0]);
    int v;
    char ctr = '\0';
    while (ctr != '\n'){
        scanf("%d%c", &v, &ctr);
        if (v != -1)
            Merge(v);
    }
    Print(root[0]);
    return 0;
}