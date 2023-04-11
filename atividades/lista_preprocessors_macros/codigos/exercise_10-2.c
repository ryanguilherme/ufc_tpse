#include <stdio.h>

#define is_digit(value) ((value - (int)value) > 0 ? 1 : 0)

int main(){
    float value;
    while (1){
        scanf("%f", &value);
        if (is_digit(value)){
            printf("decimal");
        }else{
            printf("nao decimal");
        }
    }
    return 0;
}