#include <stdio.h>

#define is_digit(value) (((value) >= 0) && ((value) <= 9)) ? 1 : 0

#define is_hex(value) (((is_digit(value) || (((value) >= "a") && ((value) <= "f") || (((value) >= "A") && ((value) <= "F"))))) ? 1 : 0)

int main(){
    if ((is_hex(123)) == 1){
        printf("hexadecimal");
    }else{
        printf("nao hexadecimal");
    }
}