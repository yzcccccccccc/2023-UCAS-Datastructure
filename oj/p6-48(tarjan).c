#include<stdio.h>
#include<stdlib.h>
#define SIZE 1919810
#define LEN 1010

char u, v;

typedef struct Node{
    char val;
    struct Node *lc, *rc, *pa;
}Node;

int _index;
char line[SIZE];

Node *root;

Node *EstablishTree(){
    Node *p;
    _index++;
    if (line[_index] == '^' || line[_index] == '\0')  return NULL;
    p = (Node *)malloc(sizeof(Node));
    p->val = line[_index];
    p->lc = EstablishTree();
    p->rc = EstablishTree();
    return p;
}

int fa[LEN], vis[LEN];
int find(int x){
    if (fa[x] != x)
        fa[x] = find(fa[x]);
    return fa[x];
}

void merge(int x, int y){
    int x_f = find(x);
    int y_f = find(y);
    if (x_f != y_f)
        fa[y_f] = x_f;
    return;
}

char ans;
void Tarjan(Node *p){
    if (p == NULL)  return;
    Tarjan(p->lc);
    if (p->lc != NULL)  merge((int)(p->val), (int)(p->lc->val));
    Tarjan(p->rc);
    if (p->rc != NULL)  merge((int)(p->val), (int)(p->rc->val));
    vis[p->val] = 1;
    if (p->val == u && vis[u] && vis[v])   ans  = find(v);
    return;
}

int main(){
    scanf("%s", line);
    _index = -1;
    root = EstablishTree();
    for (int i = 0; i < LEN; i++)  fa[i] = i;
    scanf("\n%c %c", &u, &v);
    Tarjan(root);
    printf("%c", ans);
    return 0;
}