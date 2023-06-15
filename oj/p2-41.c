#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#define inf -1


int max_exp = inf;

typedef struct Node{
    struct Node *next, *prior;
    int coe, exp;
}Link;

Link *Init(){
    Link *head = (Link *)malloc(sizeof(Link));
    //*head point to a head node
    head->coe = head->exp = -1;
    head->next = head->prior = head;
    return head;
}

Link *Query(Link *list, int exp){
    Link *p = list->next;
    while (p != list){
        if (p->exp == exp)
            return p;
        p = p->next;
    }
    return NULL;
}

void Insert(Link *list, int coe, int exp){
    Link *p = Query(list, exp);
    if (p != NULL){
        p->coe += coe;
    }
    else{
        p = list->next;
        while (p->next != list) p = p->next;
        Link *pp = (Link *)malloc(sizeof(Link));
        pp->coe = coe;
        pp->exp = exp;
        pp->next = list;
        pp->prior = p;
        p->next = pp;
        list->prior = pp;
    }
    return;
}

void input(Link *list){
    char c = getchar();
    int sign = 1, coe, exp;
    while (c != '\n'){
        while (c == ' ') c = getchar();
        if (c == '-' || c == '+'){
            sign = (c == '-') ? -1 : 1;
            c = getchar();
        }
        while (c == ' ') c = getchar();
        coe = 0;
        while (c >= '0' && c <= '9'){
            coe = coe * 10 + c - '0';
            c = getchar();
        }
        if (c == ' ' || c == '\n'){
            max_exp = (max_exp < 0) ? 0 : max_exp;
            if (c == '\n')
                break;
            else
                continue;
        }
        else{
            coe = (coe == 0) ? 1 : coe;
            coe = coe * sign;
            c = getchar();
            if (c == '^'){
                exp = 0;
                c = getchar();
                while (c >= '0' && c <= '9'){
                    exp = exp * 10 + c - '0';
                    c = getchar();
                }
            }
            else{
                exp = 1;
            }
            max_exp = (max_exp < exp - 1) ? exp - 1 : max_exp;
            Insert(list, exp * coe ,exp - 1);
            while (c == ' ') c =getchar();
        }
    }
    return;
}

void Print(Link *list){
    Link *p = list->next;
    while (p != list){
        printf("(%d, %d)", p->coe, p->exp);
        p = p->next;
    }
    printf("\n");
    return;
}



int main(){
    Link *list = Init();
    input(list);
    //Print(list);
    int out = 0;
    for (int i = max_exp, coe; i >= 0; i--){
        Link *p = Query(list ,i);
        if (!p) continue;
        coe = p->coe;
        if (coe != 0){
            out = 1;
            if (coe < 0){
                printf("- %d", -coe);
            }
            else{
                (i == max_exp) ? printf("%d", coe) : printf("+ %d", coe);
            }
            if (i != 0) printf("x");
            (i > 1) ? printf("^%d ", i) : printf(" ");
        }
    }
    if (!out)
        printf("0\n");
    return 0;
}