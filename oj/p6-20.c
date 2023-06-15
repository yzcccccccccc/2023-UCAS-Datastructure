#include<stdio.h>
#define N 10000010

int n;
typedef struct Node{
    int u, l, bro;
}Node;

int visit[N], L[N], R[N];
int L1[N], R1[N];

Node Tree[N];

void Create_tree(int node){
    if (node == 0)  return;
    visit[node] = 1;
    L[node] = Tree[node].l;
    Create_tree(L[node]);
    R[node] = Tree[node].bro;
    Create_tree(R[node]);
    return;
}

void Forest2Tree(){
    int pre_node = 1;
    L[0] = R[0] = 1;
    Create_tree(1);
    for (int i = 2; i <= n; i++)
        if (!visit[i]){
            R[pre_node] = i;
            Create_tree(i);
            pre_node = i;
        }
    return;
}

void Print(int *Lp, int *Rp){
    for (int i = 0; i <= n; i++)
        printf("%d%c", Lp[i], (i == n) ? '\n' : ' ');
    for (int i = 0; i <= n; i++)
        printf("%d%c", Rp[i], (i == n) ? '\n' : ' ');
    return;
}

int pre;
void visit_pre_order(int node){
    if (node == 0)  return;
    L1[node] = L[node];
    R1[node] = R[node];
    if (L[node] == 0)
        L1[node] = pre;
    pre = node;
    visit_pre_order(L[node]);
    visit_pre_order(R[node]);
    return;
}
void visit_infix_order(int node){
    if (node == 0)  return;
    L1[node] = L[node];
    R1[node] = R[node];
    visit_infix_order(L[node]);
    if (L[node] == 0)
        L1[node] = pre;
    if (R[pre] == 0)
        R1[pre] = node;
    pre = node;
    visit_infix_order(R[node]);
    return;
}
void visit_post_order(int node){
    if (node == 0)  return;
    L1[node] = L[node];
    R1[node] = R[node];
    visit_post_order(L[node]);
    visit_post_order(R[node]);
    if (R[pre] == 0)
        R1[pre] = node;
    pre = node;
    return;
}

int main(){
    scanf("%d", &n);
    for (int i = 0, u, l, bro; i < n; i++){
        scanf("%d%d%d", &u, &l, &bro);
        Tree[u].u = u;
        Tree[u].l = l;
        Tree[u].bro = bro;
    }
    Forest2Tree();

    //pre order
    pre = 0;
    L1[0] = R1[0] = L[0];
    visit_pre_order(1);
    Print(L1, R1);

    //infix order
    pre = 0;
    L1[0] = R1[0] = L[0];
    visit_infix_order(1);
    Print(L1, R1);

    //post order
    pre = 0;
    L1[0] = R1[0] = L[0];
    visit_post_order(1);
    Print(L1, R1);
    return 0;
}