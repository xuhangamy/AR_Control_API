#include <ardrone/basic/fixit.h>

#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>

void whu::vardump_hex(const void* var, int size) {
	int i,j;
	const uint8_t* dt = (uint8_t*)var;
	char c[16];
	for (i = 0; i < size; i++) {
		if (i%16==0) {
			printf("\n%.8X:  ", i / 16);
		}
		printf("%.2X", dt[i]);
		if (0x21<=dt[i]&&dt[i]<=0x7e) {
			c[i % 16] = dt[i];
		} else {
			c[i % 16] = '.';
		}
		if (i%2!=0) {
			printf(" ");
		}
		if (i%16==15) {
			printf("\t");
			for (j = 0; j < 16; j++) {
				printf("%c", c[j]);
			}
		}
	}
	for (int i = 0; i < (16-size%16)/2; i++) {
		printf("     ");
	}
	printf("\t");
	for (j = 0; j < size % 16; j++) {
		printf("%c", c[j]);
	}
	printf("\n");
}
void whu::check_status(bool status, const char* info) {
	if (!status) {
		printf("%s\n", info);
		abort();
	}
}