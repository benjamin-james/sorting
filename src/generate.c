#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <inttypes.h>
#include <unistd.h>
#include <fcntl.h>
int main(int argc, char **argv)
{
	if (argc < 2) {
		fprintf(stderr, "Usage: %s numbers\n", *argv);
	}
	srand(time(NULL));
	int fd;
	if ((fd = open("/dev/urandom", O_RDONLY)) == -1) {
		perror("Could not open /dev/urandom");
		return 1;
	}
	long long i, num = strtoll(argv[1], NULL, 10);
	for (i = 0; i < num; i++) {
		uint64_t tmp = 0;
		while (tmp == 0 || tmp >= INT64_MAX) {
			if (read(fd, &tmp, sizeof tmp) < 0) {
				perror("read");
				return 1;
			}
		}
		printf("%" PRIu64 "\n", tmp);
	}
	close(fd);
	return 0;
}
