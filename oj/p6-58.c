#include<stdio.h>
#include<string.h>
#define N 10000010

int L[N], R[N], L1[N], R1[N], l1, l2;
int target;

void Print(){
    for (int i = 0; i < l1; i++)
        printf("%d ", L[i]);
    printf("\n");
    for (int i = 0; i < l1; i++)
        printf("%d ", R[i]);
    printf("\n");
    printf("%d\n", target);
    for (int i = 0; i < l2; i++)
        printf("%d ", L1[i]);
    printf("\n");
    for (int i = 0; i < l2; i++)
        printf("%d ", R1[i]);
    printf("\n");
}

int bias;
void insert_tree(){
    R1[1] = L[target];
    for (int i = 1; i < l2; i++){
        L[L1[0] + i - 1] = L1[i];
        R[R1[0] + i - 1] = R1[i];
    }
    L[target] = L1[0];
    return;
}

int ans[N], ans_l;
void Print_mid(int node){
    if (node == 0) return;
    Print_mid(L[node]);
    ans[ans_l++] = node;
    Print_mid(R[node]);
    return;
}

void Print_ans(){
    Print_mid(1);
    for (int i = 0; i < ans_l; i++)
        printf("%d%c", ans[i], (i == ans_l - 1) ? '\n' : ' ');
    return;
}

int main(){
    int x;
    char c;
    l1 = 0;
    while (scanf("%d%c", &x, &c) == 2){
        L[l1] = x;
        l1++;
        if (c == '\n')  break;
    }
    l1 = 0;
    while (scanf("%d%c", &x, &c) == 2){
        R[l1] = x;
        l1++;
        if (c == '\n')  break;
    }
    scanf("%d%c", &target, &c);
    l2 = 0;
    while (scanf("%d%c", &x, &c) == 2){
        L1[l2] = x;
        l2++;
        if (c == '\n')  break;
    }
    l2 = 0;
    while (scanf("%d%c", &x, &c) == 2){
        R1[l2] = x;
        l2++;
        if (c == '\n')  break;
    }
    //Print();
    insert_tree();
    Print_ans();
    return 0;
}