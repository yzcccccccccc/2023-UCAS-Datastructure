#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#define stack_size 1919810
#define LEN 1919810

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

Status Empty(Stack *s){
    return s->top == -1;
}


int main(){
    char line[LEN];
    int len, mark;
    ElemType val;
    while (scanf("%s", line) != EOF){
        len = strlen(line) - 1;
        //printf("%d\n", len);
        mark = 0;
        Stack *s= Init();
        for (int i = 0; i < (len >> 1); i++)
            Push(s, line[i]);
        for (int i = (len & 1) ? (len >> 1) + 1 : (len >> 1); line[i] != '@' && !mark; i++){
            if (Pop(s, &val)){
                if (val != line[i])
                    mark = 1;
            }
            else
                mark = 1;
            //printf("%c %c\n", line[i], val);
        }
        if (!mark)
            printf("1\n");
        else
            printf("0\n");
    }
    return 0;
}