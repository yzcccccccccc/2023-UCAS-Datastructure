#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#define LEN 10000010

char str[LEN], tmp_str[LEN], ans_str[LEN];
int len, ans_len, ans_loc;

int check(int l){
    for (int i = 0; i < len - l + 1; i++){
        memset(tmp_str, 0, sizeof(tmp_str));
        memcpy(tmp_str, str + i, l);
        tmp_str[l] = '\0';
        //printf("%s\n", tmp_str);
        if (strstr(str + i + 1, tmp_str) != NULL)
            return i;
    }
    return -1;
}

void solve(){
    int l = 1, r = len - 1, mid, tmp;
    while (l < r){
        //printf("%d %d\n", l, r);
        mid = (l + r) >> 1;
        tmp = check(mid);
        if (tmp != -1){
            if (mid > ans_len){
                ans_len = mid;
                ans_loc = tmp;
                strcpy(ans_str, tmp_str);
            }
            l = mid + 1;
        }
        else
            r = mid;
    }
    tmp = check(r);
    if (tmp != -1){
        if (r > ans_len){
            ans_len = r;
            ans_loc = tmp;
            strcpy(ans_str, tmp_str);
        }
    }
    return;
}

int main(){
    gets(str);
    len = strlen(str);
    ans_len = -1;
    //printf("%d\n", check(4));
    solve();
    if (ans_len != -1)
        printf("%s %d\n", ans_str, ans_loc);
    else
        printf("%d\n", ans_len);
    return 0;
}