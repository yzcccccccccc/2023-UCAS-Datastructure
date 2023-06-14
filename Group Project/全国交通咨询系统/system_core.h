/*
    This file includes the basic functions of the consulting system.
    Including: Graph Constructing, Path Algorithm, Graph Edit etc.
*/
#include<stdio.h>
#include<string.h>
#include<stdlib.h>

#define INF 1e9+7

#define MAXLEN 10
#define ID_MAXLEN 6
#define City_MAXLEN 10
#define Verx_MAXNUM 100
#define Route_Len 100
#define Info_MAXLEN 100

#define DAY_MINUTES 1440

// Below are some Error Code
#define DEP_CITY_NOT_IN 1
#define ARR_CITY_NOT_IN 2

#define CITY_IN_LIST 1
#define CITY_NOT_IN_LIST 2

#define ROUTE_NOT_IN 1

#define NO_ROUTE_AVAILABLE 3      // No route from dep_city to arr_city

#define FILE_ERR 1

typedef struct RouteInfo{
    char dep_city[City_MAXLEN], arr_city[City_MAXLEN];
    char id[ID_MAXLEN];
    int dep_time, arr_time;
    int price;
    int mode;       // Train = 1, Flight = 2
}RouteInfo;

void Print_info(RouteInfo info){
    printf("%s %s %s %d %d %d %s\n", 
        info.dep_city, info.arr_city, info.id, info.dep_time, info.arr_time, info.price, (info.mode == 1) ? "Train" : "Flight");
    return;
}

int TimeConvert(const void *buf){
    int h, m;
    sscanf(buf, "%d:%d", &h, &m);
    return h * 60 + m;
}

typedef struct EdgeInfo{
    int u, v;                   // from u to v
    char id[ID_MAXLEN];         // flight/train id
    int type;                   // 2: Flight, 1: Train     
    int price;

    /* 
        Use Minutes as the measurement
        e.g. 7:30 a.m. = 450
    */
    int dep_time;               // departure time
    int arr_time;               // arrival time
    int duration;
}EdgeInfo;

typedef struct EdgeNode{
    EdgeInfo elem;
    struct EdgeNode *next;
}EdgeNode;

int cmp_Edge(EdgeInfo a, EdgeInfo b){
    return a.u == b.u && a.v == b.v && a.type == b.type && a.price == b.price && a.dep_time == b.dep_time && a.duration == b.duration && !strcmp(a.id, b.id);
}

typedef struct VNode{
    int city_id;
    EdgeNode *first_edge;
}VNode;

typedef struct Graph{
    VNode verx[Verx_MAXNUM];
    int VNum;
    char city_list[Verx_MAXNUM][City_MAXLEN];
    int flags[Verx_MAXNUM];     // mask codes
}Graph;

void Print_graph(Graph G){
    int vnum = G.VNum;
    EdgeNode *p;
    printf("%10s %10s %10s %10s %10s %10s %10s\n", "dep_city", "arr_city", "ID", "dep_time", "arr_time", "price", "trans");
    for (int i = 0; i < vnum; i++){
        if (G.flags[i]){
            p = G.verx[i].first_edge;
            while (p != NULL){
                if (G.flags[p->elem.v])
                    printf("%10s %10s %10s %10d %10d %10d %10s\n", 
                        G.city_list[i], G.city_list[p->elem.v], p->elem.id, p->elem.dep_time, p->elem.arr_time, p->elem.price, (p->elem.type == 1) ? "Train" : "Flight");
                p = p->next;
            }
        }
    }
    return;
}

Graph GPH;

int Add_Route(RouteInfo info){
    //printf("Add Route\n");
    //Print_info(info);
    Graph *G = &GPH;
    
    int vnum = G->VNum;

    int u, v;
    for (u = 0; u < vnum; u++){
        if (G->flags[u] && strcmp(info.dep_city, G->city_list[u]) == 0)
            break;
    }
    if (u == vnum)  return DEP_CITY_NOT_IN;
    for (v = 0; v < vnum; v++){
        if (G->flags[v] && strcmp(info.arr_city, G->city_list[v]) == 0)
            break;
    }
    if (v == vnum)   return ARR_CITY_NOT_IN;

    EdgeInfo insert_edge;
    insert_edge.u = u;
    insert_edge.v = v;
    insert_edge.dep_time = info.dep_time;
    insert_edge.arr_time = info.arr_time;
    insert_edge.duration = info.arr_time - info.dep_time;
    insert_edge.price = info.price;
    insert_edge.type = info.mode;
    strcpy(insert_edge.id, info.id);

    EdgeNode *p = (EdgeNode *)malloc(sizeof(EdgeNode));
    p->elem = insert_edge;
    p->next = NULL;

    EdgeNode *q;
    if (G->verx[u].first_edge == NULL){
        G->verx[u].first_edge = p;
    }
    else{
        q = G->verx[u].first_edge;
        while (q->next != NULL) q = q->next;
        q->next = p;
    }

    printf("%d %d\n", u, v);
    return 0;
}

int Del_Route(RouteInfo info){
    printf("Del Route\n");
    Graph *G = &GPH;
    
    int vnum = G->VNum;

    int u, v;
    for (u = 0; u < vnum; u++){
        if (G->flags[u] && strcmp(info.dep_city, G->city_list[u]) == 0)
            break;
    }
    if (u == vnum)  return DEP_CITY_NOT_IN;
    for (v = 0; v < vnum; v++){
        if (G->flags[v] && strcmp(info.arr_city, G->city_list[v]) == 0)
            break;
    }
    if (v == vnum)   return ARR_CITY_NOT_IN;

    EdgeInfo del_edge;
    del_edge.u = u;
    del_edge.v = v;
    del_edge.dep_time = info.dep_time;
    del_edge.arr_time = info.arr_time;
    del_edge.duration = info.dep_time - info.arr_time;
    del_edge.price = info.price;
    del_edge.type = info.mode;
    strcpy(del_edge.id, info.id);

    EdgeNode *p = G->verx[u].first_edge, *q;

    while (p != NULL){
        if (cmp_Edge(p->elem, del_edge)){
            if (p == G->verx[u].first_edge){
                G->verx[u].first_edge = p->next;
            }
            else{
                q->next = p->next;
            }
            free(p);
            return 0;
        }
        q = p;
        p = p->next;
    }
    return ROUTE_NOT_IN;
}

int Add_City(char name[]){
    Graph *G = &GPH;

    int vnum = G->VNum;
    int i, finded;

    finded = 0;
    for (i = 0; i < vnum; i++){
        if (strcmp(G->city_list[i], name) == 0){
            if (G->flags[i] == 0){
                finded = 1;
                break;
            }
            else{
                return CITY_IN_LIST;
            }
        }
    }

    if (finded){
        G->flags[i] = 1;
    }
    else{
        G->flags[vnum] = 1;
        strcpy(G->city_list[vnum], name);
        G->verx[vnum].city_id = vnum;
        G->VNum++;
    }
    return 0;
}

int Del_City(char name[]){
    int vnum = GPH.VNum;
    for (int i = 0; i < vnum; i++){
        if (GPH.flags[i] && !strcmp(GPH.city_list[i], name)){
            GPH.flags[i] = 0;
            return 0;
        }
    }
    return CITY_NOT_IN_LIST;
}

/*
    DFS: Brute Force
    tra: 1 for Train,   2 for Flight
    req: 1 for Time,    2 for Cost 
*/
EdgeInfo Route_tmp[Route_Len], Route_Ans[Route_Len];
int src, dest, tra_mode, tra_req;
int Ans, Ans_Len, Ans_Day;          // Ans could be the cost(money) and the time
int Ans_cost, Ans_time;
int Visited[Verx_MAXNUM];
void RouteSearch(int cur, int cost, int time, int current_time, int len, int day){
    //printf("%s %d\n", GPH.city_list[cur], day);
    int judge = (tra_req == 0) ? time : cost;
    if (judge > Ans)    return;
    if (cur == dest){
        if (judge < Ans){
            Ans = judge;
            Ans_cost = cost;
            Ans_time = time;
            Ans_Len = len;
            Ans_Day = day;
            memcpy(Route_Ans, Route_tmp, sizeof(Route_tmp));
        }
        return;
    }
    EdgeNode *p = GPH.verx[cur].first_edge;
    for (int update_cost, update_time, update_day; p != NULL; p = p->next){
        if (!Visited[p->elem.v] && p->elem.type == tra_mode){
            Route_tmp[len] = p->elem;
            Visited[p->elem.v] = 1;
            if (current_time >= p->elem.dep_time)
                update_day = 1;
            else
                update_day = 0;
            if (cur == src)
                update_time = p->elem.duration;
            else
                update_time = time + (p->elem.dep_time - current_time) + p->elem.duration + update_day * DAY_MINUTES;
            update_cost = cost + p->elem.price;
            RouteSearch(p->elem.v, update_cost, update_time, p->elem.arr_time, len + 1, day + update_day);
            Visited[p->elem.v] = 0;
        }
    }
    return;
}

int DFS(char dep_city[], char arr_city[], int tra, int req){
    int u, v, vnum;
    vnum = GPH.VNum;
    for (u = 0; u < vnum; u++){
        if (GPH.flags[u] && !strcmp(dep_city, GPH.city_list[u]))
            break;
    }
    if (u == vnum)  return DEP_CITY_NOT_IN;
    for (v = 0; v < vnum; v++){
        if (GPH.flags[v] && !strcmp(arr_city, GPH.city_list[v]))
            break;
    }
    if (v == vnum)  return ARR_CITY_NOT_IN;

    Ans = INF;
    Ans_Day = 0;
    dest = v;
    src = u;
    tra_mode = tra;
    tra_req = req;
    memset(Visited, 0, sizeof(Visited));
    Visited[src] = 1;
    RouteSearch(u, 0, 0, 0, 0, 0);
    if (Ans == INF)
        return NO_ROUTE_AVAILABLE;
    else
        return 0;
}

int LoadFile(){
    FILE *p = fopen("data.txt", "r");
    if (p == NULL){
        printf("File Error\n");
        return FILE_ERR;
    }
    char tra_mode[MAXLEN];
    char dep_time[MAXLEN], arr_time[MAXLEN];
    RouteInfo info;
    
    while (!feof(p)){
        fscanf(p, "%s %s %s %s %s %s %d",
        tra_mode, info.dep_city, info.arr_city, info.id,
        dep_time, arr_time, &info.price
        );
        info.arr_time = TimeConvert(arr_time);
        info.dep_time = TimeConvert(dep_time);
        info.mode = tra_mode[0] == 'T' ? 1 : 0;
        Add_City(info.arr_city);
        Add_City(info.dep_city);
        Add_Route(info);
        Print_info(info);
    }
    return 0;
}
