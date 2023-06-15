#include<stdio.h>
#include<string.h>
#define MAXLEN 10

#define IDLE 0
#define QUO 1
#define ANO 2
#define I_SLASH 3
#define A_STAR 4
#define Q_SLASH 5

int main(){
    char ctr;
    int state = IDLE, next_state;
    while (scanf("%c", &ctr) != EOF){
        switch (state){
        case IDLE:
            if (ctr == '/'){
                next_state = I_SLASH;
            }
            else{
                if (ctr == '\"'){
                    next_state = QUO;
                    printf("%c", ctr);
                }
                else{
                    next_state = IDLE;
                    printf("%c", ctr);
                }
            }
            break;
        case I_SLASH:
            if (ctr == '*'){
                next_state = ANO;
            }
            else{
                next_state = IDLE;
                printf("/%c", ctr);
            }
            break;
        case ANO:
            if (ctr == '*'){
                next_state = A_STAR;
            }
            else{
                next_state = ANO;
            }
            break;
        case A_STAR:
            if (ctr == '/'){
                next_state = IDLE;
            }
            else{
                if (ctr == '*'){
                    next_state = A_STAR;
                }
                else{
                    next_state = ANO;
                }
            }
            break;
        case QUO:
            if (ctr == '\\'){
                next_state = Q_SLASH;
            }
            else{
                if (ctr == '\"'){
                    next_state = IDLE;
                }
                else{
                    next_state = QUO;
                }
            }
            printf("%c", ctr);
            break;
        case Q_SLASH:
            next_state = QUO;
            printf("%c", ctr);
            break;
        default:
            break;
        }
        state = next_state;
    }
    return 0;
}