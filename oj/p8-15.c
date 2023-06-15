#include<stdio.h>
#include<stdlib.h>

int highbound, lowbound, blocksize;

int main(){
    scanf("%d%d%d", &lowbound, &highbound, &blocksize);
    int tag, last_tag, addr, size, allot_mark, first;
    last_tag = size = allot_mark = first = 0;
    addr = lowbound;
    int printed = 0;
    while (scanf("%d", &tag) != EOF){
        if (tag == 0){
            if (last_tag == 1){
                size = blocksize;
            }
            else{
                size += blocksize;
            }
        }
        else{
            if (last_tag == 0 && first){
                if (!printed)
                    printed = 1;
                else
                    printf("\n");
                printf("0 %d %d", addr - size, size);
                allot_mark = 1;
            }
        }
        last_tag = tag;
        first = 1;
        addr += blocksize;
    }
    if (last_tag == 0){
        if (!printed)
            printed = 1;
        else
            printf("\n");
        printf("0 %d %d", addr - size, size);
        allot_mark = 1;
    }
    if (!allot_mark)
        printf("0 0 0");
    return 0;
}