#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define SIZE 1010

typedef struct Node{
    int v, col, row;
    struct Node *right, *down;
}Node;

typedef struct CrossLink{
    Node *row[SIZE], *col[SIZE];
    //n:row, m:col, l:not zero
    int n, m, l;
}CrossLink;

CrossLink *Init(int n, int m){
    CrossLink *L;
    L = (CrossLink *)malloc(sizeof(CrossLink));
    memset(L->row, 0, sizeof(L->row));
    memset(L->col, 0, sizeof(L->col));
    L->n = n;
    L->m = m;
    return L;
}

void Insert(int r, int c, int v, CrossLink *L){
    Node *p = (Node *)malloc(sizeof(Node));
    Node *q, *q_pre;
    //printf("insert %d %d %d\n", r, c, v);
    p->col = c;
    p->row = r;
    p->v = v;
    p->right = p->down = NULL;
    if (L->row[r] == NULL || L->row[r]->col > c){
        p->right = L->row[r];
        L->row[r] = p;
    }
    else{
        q = q_pre = L->row[r];
        while (q != NULL && q->col < c){
            if (q != L->row[r])
                q_pre = q_pre->right;
            q = q->right;
        }
        p->right = q_pre->right;
        q_pre->right = p;

    }
    if (L->col[c] == NULL || L->col[c]->row > r){
        p->down = L->col[c];
        L->col[c] = p;
    }
    else{
        q_pre = q = L->col[c];
        while (q != NULL && q->row < r){
            if (q != L->col[c])
                q_pre = q_pre->down;
            q = q->down;
        }
        p->down = q_pre->down;
        q_pre->down = p;
    }
    return;
}

void Del(int r, int c, CrossLink *L){
    Node *p, *q, *p_pre, *q_pre;
    p_pre = p = L->row[r];
    q_pre = q = L->col[c];
    while (p != NULL && p->col != c){
        if (p != L->row[r])
            p_pre = p_pre->right;
        p = p->right;
    }
    while (q != NULL && q->row != r){
        if (q != L->col[c])
            q_pre = q_pre->down;
        q = q->down;
    }
    if (p == L->row[r]){
        L->row[r] = p->right;
    }
    else
        p_pre->right = p->right;
    if (q == L->col[c]){
        L->col[c] = q->down;
    }
    else
        q_pre->down = q->down;
    free(p);
    return;
}

Node *Query(int r, int c, CrossLink *L){
    Node *p = L->row[r];
    while (p != NULL && p->col != c)    p = p->right;
    if (p == NULL) 
        return NULL;
    else{
        return p;
    }
}

int val[SIZE * SIZE], l;
int result[SIZE * SIZE], r_l;
void getV(){
    char c = getchar();
    int rt = 0;
    int sign = 1;

    l = 0;
    while ((c = getchar()) != '\n'){
        if (c == '-'){
            sign = -1;
            continue;
        }
        if (c >= '0' && c <= '9'){
            rt = rt * 10 + c - '0';
        }
        if (c == ' '){
            val[l] = sign * rt;
            rt = 0;
            sign = 1;
            l++;
        }
    }
    val[l] = rt * sign;
    //for (int i = 0; i <= l; i++)    printf("%d ", val[i]);
    //printf("\n");
    return;
}

void Print(CrossLink *L){
    Node *p;
    printf("\n");
    for (int i = 0; i < L->n; i++){
        for (int j = 0; j < L->m; j++){
            p = Query(i, j, L);
            if (p == NULL)
                printf("0 ");
            else
                printf("%d ", p->v);
        }
        printf("\n");
    }
    return;
}

int main(){
    CrossLink *L;
    int n, m, v;
    scanf("%d%d", &n, &m);
    L = Init(n, m);
    getV();
    l = 0;
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++){
            scanf("%d", &v);
            if (v){
                Insert(i, j, val[l], L);
                l++;
            }
        }
    //Print(L);
    getV();
    r_l = l = 0;
    Node *p;
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++){
            scanf("%d", &v);
            if (v){
                p = Query(i, j, L);
                if (p == NULL)
                    Insert(i, j, val[l], L);
                else{
                    p->v += val[l];
                    if (p->v == 0)
                        Del(i, j, L);
                }
                l++;
                //Print(L);
            }
        }
    //Print(L);
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++){
            p = Query(i, j, L);
            if (p != NULL && p->v != 0){
                result[r_l++] = p->v;
            }
        }
    if (r_l == 0){
        printf("\n");
        for (int i = 0; i < n; i++)
            for (int j = 0; j < m; j++)
                printf("%d%c", 0, (j == m - 1)?'\n':' ');
    }
    else{
        for (int i = 0; i < r_l; i++)
            printf("%d%c", result[i], (i == r_l - 1)? '\n' : ' ');
        for (int i = 0; i < n; i++)
            for (int j = 0; j < m; j++){
                p = Query(i, j, L);
                printf("%d%c", (p == NULL ? 0 : 1), (j == m - 1 ? '\n' : ' '));
            }
    }
    return 0;
}