#include<stdio.h>
#define MAXLEN 100010

int a[MAXLEN], al;
int b[MAXLEN], bl;
int c[2 * MAXLEN] ,cl;

int main(){
    int v;
    char ctr = '\0';
    while (ctr != '\n'){
        scanf("%d%c", &v, &ctr);
        a[al++] = v;
    }
    ctr = '\0';
    while (ctr != '\n'){
        scanf("%d%c", &v, &ctr);
        b[bl++] = v;
    }
    for (int k = 0, i = 0, j = 0; k < al + bl; k++){
        if (i >= al){
            c[k] = b[j];
            j++;
        }
        else{
            if (j >= bl){
                c[k] = a[i];
                i++;
            }
            else{
                if (a[i] < b[j]){
                    c[k] = a[i];
                    i++;
                }
                else{
                    c[k] = b[j];
                    j++;
                }
            }
        }
    }
    for (int i = 0; i < al + bl; i++){
        printf("%d", c[i]);
        if (i != al + bl - 1)   printf(" ");
    }
    return 0;
}