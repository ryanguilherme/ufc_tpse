// Online C compiler to run C program online
#include <stdio.h>
#include <stdbool.h>
#include <math.h>

int setBits(bool w, unsigned int i, unsigned int j, unsigned int value){
    if ((i < 0) || (j > 31) || (j < i)){
        return -1; //false quando os limites de i e j estiverem errados
    }
    unsigned int mask = 0;
    for (int it = 0; it <= j; it ++){
        if (it == i){
            mask += pow(2, i);
            i++;
        }
    }
    if (w){
        value |= mask;
    }else{
        value ^= mask;
        value &= ~mask;
    }
    return value;
}

int main() {
    
    int w, i, j, value;
    scanf("%d%d%d%d", &w, &i, &j, &value);
    
    int res = setBits(w, i, j, value);
    printf("%d", res);
    
}






