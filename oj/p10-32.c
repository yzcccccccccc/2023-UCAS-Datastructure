#include<stdio.h>

int bucket[4];

int main(){
    int v;
    while (scanf("%d", &v) != EOF) bucket[v]++;
    int printed = 0;
    for (int i = 1 ; i <= 3; i++){
        while (bucket[i]){
            if (printed)    printf(" ");
            printed = 1;
            printf("%d", i);
            bucket[i]--;
        }
    }
    return 0;
}