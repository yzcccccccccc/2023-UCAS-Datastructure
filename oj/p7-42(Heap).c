#include<stdio.h>
#define N 100010
#define INF 11451419

typedef struct Edge{
    int v, c, next;
}Edge;

Edge edge[4 * N];
int len, First[N];

int n, s;

void Add_Edg(int u, int v, int c){
    len++;
    edge[len].v = v;
    edge[len].c = c;
    edge[len].next = First[u];
    First[u] = len;
    return;
}

// Heap
typedef struct Node{
    int dist, u;
}Node;

Node Heap[N];
int Hlen, vis[N];

void Adjust_Foot(int pos){
    int par = pos >> 1;
    if (par == 0)   return;
    Node tmp;
    if (Heap[pos].dist < Heap[par].dist){
        tmp = Heap[par];
        Heap[par] = Heap[pos];
        Heap[pos] = tmp;
        Adjust_Foot(par);
    }
    return;
}

void Adjust_Head(int pos){
    int child = pos * 2;
    if (child > Hlen) return;
    if (child + 1 <= Hlen && Heap[child + 1].dist < Heap[child].dist)
        child++;
    if (Heap[pos].dist > Heap[child].dist){
        Node tmp = Heap[pos];
        Heap[pos] = Heap[child];
        Heap[child] = tmp;
        Adjust_Head(child);
    }
    return;
}

void Add_Elem(Node ELEM){
    Hlen ++;
    Heap[Hlen] = ELEM;
    Adjust_Foot(Hlen);
    return;
}

int GetTop(){
    int rtVal = Heap[1].u;
    if (Hlen == 0)  return 0;
    Heap[1] = Heap[Hlen];
    Hlen--;
    Adjust_Head(1);
    return rtVal;
}

int dis[N];

int main(){
    scanf("%d %d", &n, &s);
    for (int u, v, c; scanf("%d-%d %d", &u, &v, &c) != EOF;){
        Add_Edg(u, v, c);
        Add_Edg(v, u, c);
    }
    for (int i = 1; i <= n; i++){
        dis[i] = (i == s) ? 0 : INF;
        Node tmp;
        tmp.u = i;
        tmp.dist = dis[i];
        Add_Elem(tmp);
    }
    for (int j = 2; j <= n; j++){
        int min_u = GetTop();
        while (min_u != 0 && vis[min_u]) min_u = GetTop();
        if (!min_u) break;
        vis[min_u] = 1;
        Node tmp;
        for (int i = First[min_u]; i; i = edge[i].next){
            if (dis[min_u] + edge[i].c < dis[edge[i].v]){
                dis[edge[i].v] = dis[min_u] + edge[i].c;
                tmp.u = edge[i].v;
                tmp.dist = dis[edge[i].v];
                Add_Elem(tmp);
            }
        }
    }
    for (int i = 1; i <= n; i++)
        if (i != s)
            printf("%d%c", dis[i], (i == n ? '\n' : ','));
    return 0;
}