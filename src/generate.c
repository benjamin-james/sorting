#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>
#include <unistd.h>
#include <fcntl.h>
int main(int argc, char **argv)
{
	if (argc < 2) {
		fprintf(stderr, "Usage: %s numbers\n", *argv);
		return 1;
	}
	int fd;
	if ((fd = open("/dev/urandom", O_RDONLY)) == -1) {
		perror("Could not open /dev/urandom");
		return 1;
	}
	uintmax_t i, num = strtoumax(argv[1], NULL, 10);
	for (i = 0; i < num; i++) {
	        intmax_t tmp = INTMAX_MIN;
		while (tmp == INTMAX_MIN || tmp == INTMAX_MAX) {
			if (read(fd, &tmp, sizeof tmp) < 0) {
				perror("read");
				return 1;
			}
		}
		printf("%" PRIdMAX "\n", tmp);
	}
	close(fd);
	return 0;
}
