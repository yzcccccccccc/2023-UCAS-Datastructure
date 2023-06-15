#include<stdio.h>
#include<stdlib.h>

typedef struct Node{
    int val;
    struct Node *lc, *rc;
}Node;

Node *root;

void Insert(int v){
    Node *p = (Node *)malloc(sizeof(Node));
    p->val = v;
    p->lc = p->rc = NULL;
    if (root == NULL){
        root = p;
    }
    else{
        Node *q, *par;
        q = par = root;
        while (q != NULL){
            par = q;
            if (v > q->val){
                q = q->lc;
            }
            else{
                q = q->rc;
            }
        }
        if (v > par->val)
            par->lc = p;
        else
            par->rc = p;
    }
}

int printed, x;
void Print(Node *p){
    if (p == NULL)  return;
    Print(p->lc);
    if (p->val >= x){
        if (printed)
            printf(" ");
        printed = 1;
        printf("%d", p->val);
    }
    Print(p->rc);
    return;
}

int main(){
    int val;
    char ctr = '\0';
    while (ctr != '\n'){
        scanf("%d%c", &val, &ctr);
        Insert(val);
    }
    scanf("%d", &x);
    Print(root);
    return 0;
}