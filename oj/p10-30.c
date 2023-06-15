#include<stdio.h>
#define MAXLEN 10010
#define INF 1e9 + 7

int val[MAXLEN], n;

int stack[MAXLEN][2], top;

void InsertSort(int l, int r){
    for (int i = l, min, pos, tmp; i < r; i++){
        min = INF;
        for (int j = i; j < r; j++){
            if (val[j] < min){
                min = val[j];
                pos = j;
            }
        }
        tmp = val[pos];
        val[pos] = val[i];
        val[i] = tmp;
    }
    return;
}

int QuickSort(int l, int r){
    int last = l + 1;
    for (int i = l + 1, tmp; i < r; i++){
        if (val[i] < val[l]){
            tmp = val[i];
            val[i] = val[last];
            val[last] = tmp;
            last++;
        }
    }
    return last - 1;
}

void Print(){
    for (int i = 0; i < n; i++)
        printf("%d%c", val[i], (i == n - 1) ? '\n' : ' ');
    printf("\n");
    return;
}

int main(){
    while (scanf("%d", &val[n]) != EOF) n++;
    // 0 ~ n - 1
    stack[0][0] = 0;
    stack[0][1] = n;
    top = 1;
    int l, r, bound;
    while (top){
        top--;
        l = stack[top][0];
        r = stack[top][1];
        //printf("%d %d %d\n", top, l, r);
        if (r - l <= 3) 
            InsertSort(l, r);
        else{
            bound = QuickSort(l, r);

            int tmp = val[l];
            val[l] = val[bound];
            val[bound] = tmp;

            stack[top][0] = l;
            stack[top][1] = bound;
            top++;
            stack[top][0] = bound + 1;
            stack[top][1] = r;
            top++;
        }
        
        //Print();
    }
    Print();
    return 0;
}