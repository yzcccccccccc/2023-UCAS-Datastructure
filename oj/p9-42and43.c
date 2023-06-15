#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define LEN 114514

typedef struct Node{
    int tag;
    struct Node *next[26];
}Node;

Node *Trie;

Node *New(){
    Node *p = (Node *)malloc(sizeof(Node));
    p->tag = 0;
    for (int i = 0; i < 26; i++)    p->next[i] = NULL;
    return p;
}

void Init(){
    Trie = New();
    return;
}

void Insert(char *ptr, Node *p){
    if (*ptr == '\0')   return;
    if (p->next[(*ptr) - 'a'] != NULL)
        Insert(ptr + 1, p->next[(*ptr) - 'a']);
    else{
        p->next[(*ptr) - 'a'] = New();
        Insert(ptr + 1, p->next[(*ptr) - 'a']);
    }
    if (*(ptr + 1) == '\0') p->next[(*ptr) - 'a']->tag = 1;
    return;
}

Node *Query(char *ptr){
    Node *p = Trie;
    while (*ptr != '\0'){
        if (p == NULL)  return NULL;
        p = p->next[(*ptr) - 'a'];
        ptr++;
    }
    if (p == NULL || p->tag == 0)
        return NULL;
    else
        return p;
}

int main(){
    Init();
    char line[LEN];
    int ope;
    int printed = 0;
    while (scanf("%d %s", &ope, line) != EOF){
        if (ope == 1)   Insert(line, Trie);
        if (ope == 2){
            Node *p = Query(line);
            if (p != NULL)
                p->tag = 0;
        }
        if (ope == 3){
            if (printed)
                printf("\n");
            printed = 1;
            if (Query(line) != NULL)
                printf("True");
            else
                printf("False");
        }
    }
    return 0;
}