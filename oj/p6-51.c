#include<stdio.h>
#include<stdlib.h>
#define SIZE 1919810

typedef struct Node{
    char val;
    struct Node *lc, *rc;
}Node;

int _index;
char line[SIZE];

Node *root;

Node *EstablishTree(){
    Node *p;
    _index++;
    if (line[_index] == '#' || line[_index] == '\0')  return NULL;
    p = (Node *)malloc(sizeof(Node));
    p->val = line[_index];
    p->lc = EstablishTree();
    p->rc = EstablishTree();
    return p;
}

int Priority_check(char ope){
    if (ope == '-' || ope == '+')   return 1;
    if (ope == '*' || ope == '/')   return 2;
    return 0;
}

void Print(Node *p, Node *pre){
    if (p == NULL)  return;
    int mark = 0;
    if (p->lc != NULL && !(p->lc->val >= 'a' && p->lc->val <= 'z')){
        if (Priority_check(p->val) > Priority_check(p->lc->val))
            mark = 1;
    }
    if (mark)   printf("(");
    Print(p->lc, p);
    if (mark)   printf(")");

    printf("%c", p->val);

    mark = 0;
    if (p->lc != NULL && !(p->rc->val >= 'a' && p->rc->val <= 'z')){
        if (Priority_check(p->val) > Priority_check(p->rc->val))
            mark = 1;
        if (Priority_check(p->val) == Priority_check(p->rc->val) && p->val == '-')
            mark = 1;
    }
    if (mark)   printf("(");
    Print(p->rc, p);
    if (mark)   printf(")");
    return;
}

int main(){
    scanf("%s", line);
    _index = -1;
    root = EstablishTree();
    Print(root, NULL);
    return 0;
}