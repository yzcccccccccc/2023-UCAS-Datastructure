#include<stdio.h>
#define LEN 1919810
#define SIZE 512

typedef struct Node{
    char val;
    int lc, rc, pa;
    int height;
}Node;

Node Tree[SIZE];
char line[LEN], u, v;
int _index, root;

int EstTree(int pre){
    _index ++;
    if (line[_index] == '^' || line[_index] == '\0')    return 0;
    int u = line[_index];
    Tree[u].val = line[_index];
    Tree[u].pa = pre;
    Tree[u].height = Tree[pre].height + 1;
    Tree[u].lc = EstTree(u);
    Tree[u].rc = EstTree(u);
    return u;
}

char LCA(char _u, char _v){
    if (_u == _v)   return _u;
    int u_h = Tree[_u].height;
    int v_h = Tree[_v].height;
    if (u_h > v_h)
        return LCA(Tree[_u].pa, _v);
    else
        if (u_h < v_h)
            return LCA(_u, Tree[_v].pa);
        else
            return LCA(Tree[_u].pa, Tree[_v].pa);
}

int main(){
    scanf("%s", line);
    scanf("\n%c %c", &u, &v);
    _index = -1;
    root = EstTree(0);
    u = (Tree[u].pa == 0) ? u : Tree[u].pa;
    v = (Tree[v].pa == 0) ? v : Tree[v].pa;
    //printf("%c %c\n", u, v);
    char ans = LCA(u, v);
    printf("%c\n", ans);
    return 0;
}