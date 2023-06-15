#include<stdio.h>
#include<stdlib.h>
#define INF 1e9 + 7
#define MAXLEN 10010

typedef struct Node{
    int val;
    struct Node *next;
}Node;

Node *list;

void Init(){
    list = (Node *)malloc(sizeof(Node));
    list->val = INF;
    list->next = NULL;
    return;
}

void Insert(int v){
    Node *cur = list, *p = (Node *)malloc(sizeof(Node));
    p->val = v;
    p->next = NULL;
    while (cur->next != NULL) cur = cur->next;
    cur->next = p;
    return;
}

Node *pointers[MAXLEN];
int n, p_len;

void Split(){
    Node *p = list;
    while (p->next != NULL){
        if (p->next->val < p->val){
            pointers[p_len] = p->next;
            p_len++;
        }
        p = p->next;
    }
    return;
}

int tmp[MAXLEN];
void Merge(Node *p1, Node *p2, Node *p3){
    Node *cur1 = p1, *cur2 = p2;
    int l = 0, tmp_l;
    while (cur1 != p2 || cur2 != p3){
        if (cur1 == p2){
            tmp[l] = cur2->val;
            cur2 = cur2->next;
            l++;
        }
        else{
            if (cur2 == p3){
                tmp[l] = cur1->val;
                cur1 = cur1->next;
                l++;
            }
            else{
                if (cur1->val < cur2->val){
                    tmp[l] = cur1->val;
                    cur1 = cur1->next;
                    l++;
                }
                else{
                    tmp[l] = cur2->val;
                    cur2 = cur2->next;
                    l++;
                }
            }
        }
    }
    cur1 = p1;
    tmp_l = 0;
    while (cur1 != p3){
        cur1->val = tmp[tmp_l];
        tmp_l++;
        cur1 = cur1->next;
    }
    return;
}

int printed;
void Print(){
    Node *cur = list->next;
    while (cur->val != -INF){
        if (printed) printf(" ");
        printed = 1;
        printf("%d", cur->val);
        cur = cur->next;
    }
    return;
}

int main(){
    Init();
    scanf("%d", &n);
    for (int i = 0, v; i < n; i++){
        scanf("%d", &v);
        Insert(v);
    }
    Insert(-INF);
    Split();
    for (int i = 1; i < p_len - 1; i++){
        Merge(pointers[0], pointers[i], pointers[i + 1]);
    }
    Print();
    return 0;
}
