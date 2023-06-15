#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#define stack_size 1919810

typedef char ElemType;
typedef int Status;

typedef struct mystack{
    int top;
    ElemType stack[stack_size];

}Stack;

Stack* Init(){
    Stack *s = (Stack *)malloc(sizeof(Stack));
    s->top = -1;
    return s;
}

Status Push(Stack *s, ElemType val){
    if (s->top + 1 >= stack_size)  return 0;
    ++(s->top);
    s->stack[s->top] = val;
    return 1;
}

Status Pop(Stack *s, ElemType *val){
    if (s->top == -1)   return 0;
    *val = s->stack[s->top];
    --(s->top);
    return 1;
}

int main(){
    Stack *p = Init();
    char ch = getchar();
    while (ch != '&'){
        Push(p, ch);
        ch = getchar();
    }
    ch = getchar();
    ElemType val;
    while (ch != '@'){
        Pop(p, &val);
        if (val != ch){
            printf("0\n");
            return 0;
        }
        ch = getchar();
    }
    printf("1\n");
    return 0;
}