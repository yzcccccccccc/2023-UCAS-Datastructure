#include<stdio.h>
#include<stdlib.h>
#define M 20

typedef struct Node{
    int tag;
    int addr;
    int kval;
    struct Node *llink, *rlink;
}Node;

typedef struct HeadNode{
    int nodesize;
    Node *head;
}HeadNode;

HeadNode FreeList[M];

void Init(){
    for (int i = 0; i < M; i++){
        Node *p = (Node *)malloc(sizeof(Node));
        p->addr = -1;
        p->kval = -1;
        p->llink = p->rlink = NULL;
        p->tag = 2;
        p->kval = i;
        FreeList[i].nodesize = (1 << i);
        FreeList[i].head = p;
    }
    return;
}

void AddBlock(int k, int addr){
    Node *p = FreeList[k].head;
    int block_size = FreeList[k].nodesize;
    while (p->rlink && p->rlink->addr < addr) p = p->rlink;
    Node *q = (Node *)malloc(sizeof(Node));
    q->addr = addr;
    q->kval = k;
    q->llink = p;
    q->rlink = p->rlink;
    q->tag = 0;
    if (p->rlink)
        p->rlink->llink = q;
    p->rlink = q;
    return;
}

void DelSpace(Node *p){
    p->llink->rlink = p->rlink;
    if (p->rlink)
        p->rlink->llink = p->llink;
    free(p);
    return;
}

void Recycle(int k, int addr){
    Node *p = FreeList[k].head;
    int blocksize = FreeList[k].nodesize;
    int buddy_addr = (addr % (blocksize * 2) == 0) ? addr + blocksize : addr - blocksize;

    int merge_mark = 0;
    for (;p && !merge_mark; p = p->rlink){
        if (p->addr == buddy_addr){
            merge_mark = 1;
            DelSpace(p);
            Recycle(k + 1, (buddy_addr < addr) ? buddy_addr : addr);
        }
    }
    if (!merge_mark)
        AddBlock(k, addr);
    return;
}

void PrintMem(){
    Node *p;
    int max_k = -1;
    for (int i = 0; i < M; i++)
        if (FreeList[i].head->rlink != NULL)
            max_k = (max_k < i) ? i : max_k;
    for (int i = 0; i <= max_k; i++)
        if (FreeList[i].head->rlink != NULL){
            printf("%d", i);
            p = FreeList[i].head->rlink;
            for (;p;p = p->rlink)   printf(" %d", p->addr);
            if (i != max_k) printf("\n");
        }
    return;
}

int myread(){
    char ch = getchar();
    if (ch == '\n') return -1;
    while (ch == ' ' || ch == '\n') ch = getchar();
    int rt = 0;
    while (ch >= '0' && ch <= '9'){
        rt = rt * 10 + ch - '0';
        ch = getchar();
    }
    return rt;
}

int main(){
    Init();
    int k = myread();
    int addr;
    char ope;
    while (k != -1){
        do{
            scanf("%d%c", &addr, &ope);
            AddBlock(k, addr);
        }while (ope != '\n');
        k = myread();
    }
    while (scanf("%d%d", &k, &addr) != EOF){
        Recycle(k, addr);
    }
    PrintMem();
    return 0;
}

