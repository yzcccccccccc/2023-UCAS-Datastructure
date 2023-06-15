#include<stdio.h>
#define MAXN 1000010

int set[2 * MAXN], N, M, T;

int query(int u){
    if (set[u] == u)    return u;
    return set[u] = query(set[u]);
}

void merge(int u, int v){
    set[query(u)] = query(v);
    return;
}

int main(){
    scanf("%d", &T);
    while (T){
        T--;
        scanf("%d%d", &N, &M);
        for (int i = 0; i < 2 * N; i++) set[i] = i;
        char Type[10];
        int u, v, printed = 0;
        for (int i = 0; i < M ; i++){
            scanf("%s%d%d", Type, &u, &v);
            if (Type[0] == 'A'){
                if (printed) printf("\n");
                printed = 1;
                int g_u, g_v, g_u_e, g_v_e;
                g_u = query(u);
                g_v = query(v);
                g_u_e = query(u + N);
                g_v_e = query(v + N);
                if (g_u == g_v && g_u_e == g_v_e)
                    printf("是同一个团伙所为");
                else
                    if (g_u == g_v_e && g_v == g_u_e)
                        printf("不是同一个团伙所为");
                    else
                        printf("不确定");
            }
            else{
                merge(u, v + N);
                merge(v, u + N);
            }
        }
    }
    return 0;
}