#include <stdio.h>

#define divisible(value) (((value % 10) == 0) ? 1 : 0)

int main(){
    int value;
    while (1){
        scanf("%d", &value);
        if (divisible(value)){
            printf("divisivel por 10");
        }else{
            printf("nao divisivel por 10");
        }
    }
    return 0;
}