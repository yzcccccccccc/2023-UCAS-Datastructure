#include<stdio.h>
const long long MAXINT = (1LL << 32) - 1;

long long arr[30];

int n, arrsize;
int main(){
    scanf("%d %d", &n, &arrsize);
    if (n > arrsize)
        printf("-1\n");
    else{
        arr[0] = 1;
        for (int i = 1; i < n; i++){
            arr[i] =  arr[i - 1] * i * 2;
            if (arr[i] > MAXINT){
                printf("-1\n");
                return 0;
            } 
        }
        for (int i = 0; i < n; i++)
            printf("%lld ", arr[i]);
    }
    return 0;
}