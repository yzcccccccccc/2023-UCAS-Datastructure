#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#define LEN 1919810

typedef struct Node{
    char val;
    struct Node *lc, *rc;
}Node;

char preod[LEN], infixod[LEN];
char *PREOD;
int len_infix;

Node *CreateTree(int l, int r){
    if (l >= r) return NULL;
    PREOD++;
    char v = PREOD[0];
    int pos = 0;
    for (int i = l; i < r; i++)
        if (infixod[i] == v){
            pos = i;
            break;
        }
    Node *p = (Node *)malloc(sizeof(Node));
    p->val = v;
    p->lc = CreateTree(l, pos);
    p->rc = CreateTree(pos + 1, r);
    return p;
    
}

void Print(Node *p){
    if (p == NULL)  return;
    Print(p->lc);
    Print(p->rc);
    printf("%c", p->val);
    return;
}

int main(){
    scanf("%s", preod);
    scanf("%s", infixod);
    PREOD = preod - 1;
    len_infix = strlen(infixod);
    Node *root = CreateTree(0, len_infix);
    Print(root);
    return 0;
}