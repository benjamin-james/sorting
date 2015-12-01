#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>
#include <unistd.h>
#include <fcntl.h>

#define RAND_FILE "/dev/urandom"

int main(int argc, char **argv)
{
	int fd;
	intmax_t i, num;
	char *endptr = NULL;
	if (argc < 2) {
		fprintf(stderr, "Usage: %s numbers\n", *argv);
		return 1;
	}
	if ((fd = open(RAND_FILE, O_RDONLY)) == -1) {
		perror(RAND_FILE);
		return errno;
	}
        num = strtoimax(argv[1], &endptr, 10);
	if (*endptr || num <= 0) {
		fprintf(stderr, "Please input a positive integer.\n");
		goto end;
	}
	for (i = 0; i < num; i++) {
	        intmax_t tmp = INTMAX_MIN;
		while (tmp == INTMAX_MIN || tmp == INTMAX_MAX) {
			if (read(fd, &tmp, sizeof tmp) < 0) {
				perror("read");
				goto end;
			}
		}
		printf("%" PRIdMAX "\n", tmp);
	}
end:
	close(fd);
	return errno;
}
