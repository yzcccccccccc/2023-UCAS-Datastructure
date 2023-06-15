#include<stdio.h>
#define MAXNUM 10010

int bucket[MAXNUM];

int main(){
    int max = -1, v;
    while (scanf("%d", &v) != EOF){
        if (v > max) max = v;
        bucket[v]++;
    }
    int printed = 0;
    for (int i = 0; i <= max; i++){
        while (bucket[i]){
            if (printed) printf(" ");
            printed = 1;
            printf("%d", i);
            bucket[i]--;
        }
    }
    return 0;
}