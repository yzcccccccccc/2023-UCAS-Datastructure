#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define LEN 1919810

typedef int ElemType;
typedef struct Node{
    ElemType type;
    struct Node *pre, *next;
    //type == 1(atom)
    int val;
    //type == 2(list)
    struct Node *son_list;
}Node;

char *ptr;
Node *CreatList(){
    Node *head, *p, *q;
    head = (Node *)malloc(sizeof(Node));
    head->next = NULL;
    head->pre = NULL;
    head->type = 0;
    p = head;
    ptr++;
    while (*ptr != ')'){
        if (*ptr == ','){
            ptr++;
            continue;
        }
        q = (Node *)malloc(sizeof(Node));
        p->next = q;
        q->pre = p;
        q->next = NULL;
        q->son_list = NULL;
        q->type = 0;
        if (*ptr == '('){
            q->type = 2;
            q->son_list = CreatList();
        }
        else{
            q->type = 1;
            q->val = *ptr;
        }
        ptr++;
        p = p->next;
    }
    return head;
}

void Print(Node *h){
    Node *p = h;
    if (h->next == NULL)
        printf("-1\n");
    else{
        printf("(");
        while (p != NULL){
            if (p->type == 1){
                printf("%c", p->val);
            }
            if (p->type == 2){
                Print(p->son_list);
            }
            if (p->type != 0 && p->next != NULL)    printf(",");
            p = p->next;
        }
        printf(")");
    }
    return;
}

void Del(Node *h, char v){
    Node *p = h->next, *q;
    while (p != NULL){
        if (p->type == 2){
            Del(p->son_list, v);
            if (p->son_list->next == NULL){
                p->pre->next = p->next;
                if (p->next != NULL) 
                    p->next->pre = p->pre;
                q = p;
                p = p->next;
                free(q);
            }
            else
                p = p->next;
            continue;
        }
        if (p->type == 1){
            if (p->val == v){
                p->pre->next = p->next;
                if (p->next != NULL) 
                    p->next->pre = p->pre;
                q = p;
                p = p->next;
                free(q);
                continue;
            }
            else
                p = p->next;
        }
    }
    return;
}

char line[LEN], del_v;
int main(){
    scanf("%s %c", line, &del_v);
    ptr = line;
    Node *list = CreatList();
    Del(list, del_v);
    Print(list);
    return 0;
}