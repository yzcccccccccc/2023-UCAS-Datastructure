#include<stdio.h>
#include<stdlib.h>

typedef struct Node{
    int tag;
    int size;
    int addr;
    struct Node *llink, *rlink;
}Node;

Node *pav;

void AddBound(int addr, int size, int tag){
    Node *p = (Node *)malloc(sizeof(Node));
    p->addr = addr;
    p->size = size;
    p->tag = tag;
    p->llink = pav;
    p->rlink = pav->rlink;
    pav->rlink = p;
    pav = p;
    return;
}

Node *InitBound(){
    Node *p = (Node *)malloc(sizeof(Node));
    p->llink = p->rlink = NULL;
    p->addr = -1;
    p->size = 0;
    p->tag = 2;         // Head Node
    return p;
}

void DelSpace(Node *p){
    p->llink->rlink = p->rlink;
    if (p->rlink)
        p->rlink->llink = p->llink;
    free(p);
    return;
}

int Recycle(int addr, int size){
    for (;pav && pav->rlink; pav = pav->rlink){
        if (pav->addr < addr && pav->rlink->addr > addr){
            if (pav->addr + pav->size == addr){
                if (addr + size == pav->rlink->addr){
                    pav->size += size + pav->rlink->size;
                    DelSpace(pav->rlink);
                }
                else
                    pav->size += size;
            }
            else{
                if (addr + size == pav->rlink->addr){
                    pav->rlink->size += size;
                    pav->rlink->addr = addr;
                }
                else
                    AddBound(addr, size, 0);
            }
            return 1;
        }
    }
    if (pav->addr + pav->size == addr){
        pav->size += size;
    }
    else
        AddBound(addr, size, 0);
    return 1;
}

void PrintMem(Node *p){
    for (;p;p = p->rlink){
        printf("0 %d %d", p->addr, p->size);
        if (p->rlink)   printf("\n");
    }
    return;
}

int main(){
    Node *init = InitBound();
    pav = init;
    int tag, addr, size, _free;
    _free = 0;
    while (scanf("%d%d%d", &tag, &addr, &size) == 3){
        if (!tag)
            AddBound(addr, size, tag);
        else{
            if (!_free){
                _free = 1;
                pav = init;
            }
            Recycle(addr, size);
        }
    }
    PrintMem(init->rlink);
    return 0;
}