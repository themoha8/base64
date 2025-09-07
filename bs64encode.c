#include <fcntl.h>  /* open */
#include <stdio.h>  /* fgets */
#include <stdlib.h> /* free */
#include <string.h> /* strchr */
#include <unistd.h> /* read */

#include "bs64.h" /* base64_encode */

enum { ibuf_size = 64, obuf_size = (ibuf_size + 2) / 3 * 4 + 1 };

int
main(int argc, char *argv[])
{
	char ibuf[ibuf_size];
	char obuf[obuf_size];
	char *s;
	int fd, n, i;

	if (argc > 1) {
		for (i = 1; i < argc; i++) {
			fd = open(argv[i], O_RDONLY);
			if (fd == -1) {
				perror("open");
				continue;
			}

			if ((n = read(fd, ibuf, ibuf_size - 1)) != EOF) {
				ibuf[n] = '\0';
				base64_encode(ibuf, obuf);
				puts(obuf);
			} else {
				perror("Read from file is failed");
			}
			close(fd);
		}
	} else {
		while ((fgets(ibuf, ibuf_size, stdin) != NULL)) {
			s = strchr(ibuf, '\n');
			if (s)
				*s = '\0';
			base64_encode(ibuf, obuf);
			puts(obuf);
		}
	}
	return 0;
}

/*
int
main(int argc, char *argv[])
{
	char ibuf[ibuf_size];
	char *s;
	int fd, n, i;

	if (argc > 1) {
		for (i = 1; i < argc; i++) {
			fd = open(argv[i], O_RDONLY);
			if (fd == -1) {
				perror("open");
				continue;
			}

			if ((n = read(fd, ibuf, ibuf_size - 1)) != EOF) {
				ibuf[n] = '\0';
				s = base64_encode2(ibuf);
				if (s == NULL)
					continue;
				puts(s);
			} else {
				perror("Read from file is failed");
			}
			close(fd);
			free(s);
		}
	} else {
		while ((fgets(ibuf, ibuf_size, stdin) != NULL)) {
			s = strchr(ibuf, '\n');
			if (s)
				*s = '\0';
			s = base64_encode2(ibuf);
			if (s == NULL)
				continue;
			puts(s);
			free(s);
		}
	}
	return 0;
}
*/
