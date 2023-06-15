#include<stdio.h>
#include<string.h>
#define N 10000010

typedef struct Node{
    char elem;
    int l, r;
}Node;

Node Tree[N];
int n;

int queue[N], h, t;

int check_tree(){
    int stage, v, lc, rc;
    stage = h = t = 0;
    queue[h] = 1;
    while (h <= t){
        v= queue[h];
        h++;
        lc = rc = 0;
        if (stage == 0){
            if (Tree[v].l != -1){
                t++;
                lc = 1;
                queue[t] = Tree[v].l;
            }
            if (Tree[v].r != -1){
                t++;
                rc = 1;
                queue[t] = Tree[v].r;
            }
            if (lc == 1 && rc == 0 || lc == 0 && rc == 0)
                stage = 1;
            if (lc == 0 && rc == 1)
                return 0;
        }
        else{
            if (Tree[v].l != -1 || Tree[v].r != -1)
                return 0;
        }
    }
    return 1;
}

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
    if (check_tree())
        printf("Yes");
    else
        printf("No");
    return 0;
}