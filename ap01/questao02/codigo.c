#include <stdio.h>
#include <stdlib.h>

unsigned int shift_ones(unsigned int n) {
    unsigned int result = 0;
    int count = 0;
    while (n) {
        if (n & 1) {
            result |= 1 << (sizeof(unsigned int) * 8 - 1 - count);
            count++;
        }
        n >>= 1;
    }
    return result;
}

int main() {
    unsigned int input = 112;
    unsigned int output = shift_ones(input);
    printf("Input: %u\nOutput: 0x%04x\n", input, output);
    return 0;
}
