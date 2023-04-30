#include <stdio.h>
#include <stdbool.h>
#include <math.h>

#define MASK 0x1

int numBits(int value){
    int count = 0;
    while (value != 0){
        count++;
        value >>= 1;
    }
    return count;
}

void decimalToBinary(unsigned int num, char *str) {
    if (num == 0){
        printf("0000");
        return;
    }
    if (str == NULL) return;
    int i = 0;
    do {
        str[i++] = num % 2 + '0'; 
        num /= 2;
    } while (num != 0);
    str[i] = '\0';
    int j = 0;
    i--; 
    while (j < i) { 
        char temp = str[j];
        str[j] = str[i];
        str[i] = temp;
        j++;
        i--;
    }
}

int countBitsOne(unsigned int value){
    int bitsOne = 0;
    for (int i = 0; i < 32; i++){
        if(value & MASK){
            bitsOne++;
        }
        value >>= 1;
    }
    return bitsOne;
    
}


int main(){
    unsigned int value;
    scanf("%d", &value);
    
    float bitsNumber = (float)numBits(value)/4;
    if ((bitsNumber != (int)bitsNumber)){
        bitsNumber++;
    }
    bitsNumber = (int)bitsNumber * 4;
    
    int ones = countBitsOne(value);
    unsigned int result;
    for (int i=0; i < ones; i++){
        result += pow(2,i);
    }
    for (int i = 0; i < bitsNumber - countBitsOne(result); i++){
        result <<= 1;
    }

    char stringBinary[33];
    decimalToBinary(result, stringBinary);
    printf("%s", stringBinary);
    
}















