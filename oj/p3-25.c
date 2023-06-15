#include<stdio.h>

int main(){
    int n, ans = 1;
    scanf("%d", &n);
    while (n > 0){
        ans *= n;
        n >>= 1;
    }
    printf("%d\n", ans);
    return 0;
}