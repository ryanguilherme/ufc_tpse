#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Uso: %s <LED>\n", argv[0]);
        return 1;
    }

    // Crie uma string para o caminho do arquivo do LED usando snprintf
    char ledPath[100]; // Ajuste o tamanho conforme necessário
    snprintf(ledPath, sizeof(ledPath), "/sys/class/leds/beaglebone\:green\:usr%s/brightness", argv[1]);

    // Abra o arquivo para escrita
    FILE *ledfile = fopen(ledPath, "w");
    if (ledfile == NULL) {
        perror("ERROR: could not open led file!\n");
        return 1;
    }

    // Escreva um valor no arquivo (0 no exemplo)
    fprintf(ledfile, "0");
    fclose(ledfile);
    usleep(500000);

    // Abra o arquivo novamente (outra operação)
    ledfile = fopen(ledPath, "w");
    if (ledfile == NULL) {
        perror("ERROR: could not open led file!\n");
        return 1;
    }

    // Escreva outro valor no arquivo (1 no exemplo)
    fprintf(ledfile, "1");
    fclose(ledfile);
    usleep(500000);

    return 0;
}

