#include<stdio.h>
#include<string.h>
#define N 10000010

typedef struct Node{
    char elem;
    int l, bro;
}Node;

Node Tree[N];
int n;

void Print(int node, int depth){
    if (node == -1)     return;
    for (int i = 0; i < depth; i++)
        printf("-");
    printf("%c\n", Tree[node].elem);
    Print(Tree[node].l, depth + 1);
    Print(Tree[node].bro, depth);
    return;
}

int main(){
    char c, enter;
    int p, q, v;
    while (scanf("%c %d %d%c", &c, &p, &q, &enter) != EOF){
        //printf("%d:%c %d %d\n", n + 1, c, l, r);
        ++n;
        Tree[n].elem = c;
        Tree[n].l = p;
        Tree[n].bro = q;
        //scanf("\n");
    }
    Print(1, 0);
    return 0;
}