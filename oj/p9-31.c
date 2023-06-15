#include<stdio.h>
#define LEN 114514

typedef struct Node{
    int val;
    int lc, rc;
}Node;

Node BST[LEN];
int len = 0;

// mode = 0: min->max
int check(int node, int mode){
    if (mode == 0){
        if (!(BST[BST[node].lc].val <= BST[node].val && BST[BST[node].rc].val >= BST[node].val))
            return 0;
        if (BST[node].lc != -1) check(BST[node].lc, mode);
        if (BST[node].rc != -1) check(BST[node].rc, mode);
    }
    else{
        if (!(BST[BST[node].lc].val >= BST[node].val && BST[BST[node].rc].val <= BST[node].val))
            return 0;
        if (BST[node].lc != -1) check(BST[node].lc, mode);
        if (BST[node].rc != -1) check(BST[node].rc, mode);
    }
    return 1;
}

int main(){
    int v, l, r;
    while (scanf("%d%d%d", &v, &l, &r) != EOF){
        BST[len].val = v;
        BST[len].lc = l;
        BST[len].rc = r;
        len++;
    }
    if (check(0, 0) || check(0, 1))
        printf("1");
    else
        printf("0");
    return 0;
}