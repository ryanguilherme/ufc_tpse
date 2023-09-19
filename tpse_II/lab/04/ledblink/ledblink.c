#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main() {
	while (1) {
		FILE *ledfile;
		ledfile = fopen("/sys/class/leds/beaglebone\:green\:usr0/brightness", "w");
		if (ledfile == NULL) {
			perror("ERROR: could not open led file!\n");
			return 1;
		}
		fprintf(ledfile, "0");
		fclose(ledfile);
		usleep(500000);

		ledfile = fopen("/sys/class/leds/beaglebone\:green\:usr0/brightness", "w");
                if (ledfile == NULL) {
                        perror("ERROR: could not open led file!\n");
                        return 1;
                }
                fprintf(ledfile, "1");
                fclose(ledfile);
                usleep(500000);

		ledfile = fopen("/sys/class/leds/beaglebone\:green\:usr1/brightness", "w");
                if (ledfile == NULL) {
                        perror("ERROR: could not open led file!\n");
                        return 1;
                }
                fprintf(ledfile, "0");
                fclose(ledfile);
                usleep(500000);

		ledfile = fopen("/sys/class/leds/beaglebone\:green\:usr1/brightness", "w");
                if (ledfile == NULL) {
                        perror("ERROR: could not open led file!\n");
                        return 1;
                }
                fprintf(ledfile, "1");
                fclose(ledfile);
                usleep(500000);

		ledfile = fopen("/sys/class/leds/beaglebone\:green\:usr2/brightness", "w");
                if (ledfile == NULL) {
                        perror("ERROR: could not open led file!\n");
                        return 1;
                }
                fprintf(ledfile, "0");
                fclose(ledfile);
                usleep(500000);

		ledfile = fopen("/sys/class/leds/beaglebone\:green\:usr2/brightness", "w");
                if (ledfile == NULL) {
                        perror("ERROR: could not open led file!\n");
                        return 1;
                }
                fprintf(ledfile, "1");
                fclose(ledfile);
                usleep(500000);

		ledfile = fopen("/sys/class/leds/beaglebone\:green\:usr3/brightness", "w");
                if (ledfile == NULL) {
                        perror("ERROR: could not open led file!\n");
                        return 1;
                }
                fprintf(ledfile, "0");
                fclose(ledfile);
                usleep(500000);

		ledfile = fopen("/sys/class/leds/beaglebone\:green\:usr3/brightness", "w");
                if (ledfile == NULL) {
                        perror("ERROR: could not open led file!\n");
                        return 1;
                }
                fprintf(ledfile, "1");
                fclose(ledfile);
                usleep(500000);

		return 0;
	}
}

