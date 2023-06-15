#include<stdio.h>
#define MAXLEN 10010
#define INF 1e9 + 7

// Least_Heap
int heap[MAXLEN], last;

void Adj_Head(int pos){
    int min = INF, p = -1;
    for (int i = 1; i <= 3; i++)
        if (pos * 3 + i < last){
            if (heap[pos * 3 + i] < min){
                min = heap[pos * 3 + i];
                p = i;
            }
        }
    if (p != -1 && min < heap[pos]){
        int tmp = heap[pos];
        heap[pos] = heap[pos * 3 + p];
        heap[pos * 3 + p] = tmp;
        Adj_Head(pos * 3 + p);
    }
    return;
}

void Adj_Foot(int pos){
    if (pos == 0) return;
    int par = (pos - 1) / 3;
    if (heap[pos] < heap[par]){
        int tmp = heap[par];
        heap[par] = heap[pos];
        heap[pos] = tmp;
        Adj_Foot(par);
    }
    return;
}

int get_top(){
    int val = heap[0];
    heap[0] = heap[last - 1];
    last--;
    Adj_Head(0);
    return val;
}

void insert(int v){
    heap[last] = v;
    last++;
    Adj_Foot(last - 1);
    return;
}

void Print(){
    for (int i = 0; i < last; i++)
        printf("%d", heap[i]);
    printf("\n");
    return;
}

int main(){
    int v;
    while (scanf("%d", &v) != EOF){
        insert(v);
        //Print();
    }
    int printed = 0;
    while (last){
        if (printed) printf(" ");
        printed = 1;
        printf("%d", get_top());
        //Print();
    }
    return 0;
}