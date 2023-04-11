#include <stdio.h>

#define swap(value, svalue) \
    int hold = svalue;\
    svalue = value;\
    value = hold;

int main(){
    int a = 5;
    int b = 10;
    printf("%s %d %d\n", "before swap: ", a, b);
    swap(a, b);
    printf("%s %d %d", "after swap: ", a, b);
    return 0;
}