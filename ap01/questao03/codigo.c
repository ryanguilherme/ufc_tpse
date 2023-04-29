#include <stdio.h>
#include <stdbool.h>

#define MASK 0x1


int numeroDeBits(bool w, unsigned int value){
    int um = 0;
    int zero = 0;
    for (int i = 0; i < 32; i++){
        if(value & MASK){
            um++;
        }else{
            zero++;
        }
        value >>= 1;
    }
    return w == 0 ? zero : um;
    
}


int main(){
    unsigned int value;
    int w;
    scanf("%d", &w);
    scanf("%d", &value);
    printf("%d", numeroDeBits(w, value));
    
}











