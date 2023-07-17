#include <stdio.h>

#define is_digit(value) (((value) >= 0) && ((value) <= 9)) ? 1 : 0

int main(){
    int value;
    while (1){
        scanf("%d", &value);
        if (is_digit(value)){
            printf("decimal");
        }else{
            printf("nao decimal");
        }
    }
    return 0;
}