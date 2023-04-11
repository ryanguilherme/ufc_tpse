#include <stdio.h>

#define is_hex(value)\
    for (int i=0; value[i] != "\0"; i++){\
        if (((value[i] < 65) && (value[i] > 70)) && ((value[i] < 97) && (value[i] > 102)) && ((value[i] < 0) && (value[i] < 0) && (value[i] > 9))){\
            return 0;\
        }\
    }\
    return 1;
/*
int main(){
    if ((is_hex(123)) == 1){
        printf("hexadecimal");
    }else{
        printf("nao hexadecimal");
    }
}*/