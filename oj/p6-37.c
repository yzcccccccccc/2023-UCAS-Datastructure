#include<stdio.h>
#include<string.h>
#define N 10000010

typedef struct Node{
    char elem;
    int l, r;
}Node;

Node Tree[N];
int n;
int stack[N], top;

int main(){
    char c, enter;
    int l, r, v;
    while (scanf("%c %d %d%c", &c, &l, &r, &enter) != EOF){
        //printf("%d:%c %d %d\n", n + 1, c, l, r);
        ++n;
        Tree[n].elem = c;
        Tree[n].l = l;
        Tree[n].r = r;
        //scanf("\n");
    }
    stack[top] = 1;
    //for (int i = 1; i <= n; i++)
    //    printf("%c %d %d\n", Tree[i].elem, Tree[i].l, Tree[i].r);
    while (top != -1){
        v = stack[top];
        top--;
        printf("%c ", Tree[v].elem);
        if (Tree[v].r != -1) stack[++top] = Tree[v].r;
        if (Tree[v].l != -1) stack[++top] = Tree[v].l;
    }
    return 0;
}