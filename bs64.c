#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "bs64.h"

static const char bs64_encode_map[] = {
	'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P',
	'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z', 'a', 'b', 'c', 'd', 'e', 'f',
	'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v',
	'w', 'x', 'y', 'z', '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', '+', '/',
};

static const char bs64_decode_map[256] = {
    -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
    -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
    -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 62, -1, -1, -1, 63,
    52, 53, 54, 55, 56, 57, 58, 59, 60, 61, -1, -1, -1, -1, -1, -1,
    -1,  0,  1,  2,  3,  4,  5,  6,  7,  8,  9, 10, 11, 12, 13, 14,
    15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, -1, -1, -1, -1, -1,
    -1, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40,
    41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 51, -1, -1, -1, -1, -1,
    -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
    -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
    -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
    -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
    -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
    -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
    -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
    -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
};

void
base64_encode(const char *ibuf, char *obuf)
{
	int i, j = 0, c = 0;
	char tmp[3];

	for (i = 0; ibuf[i] != '\0'; i++) {
		tmp[c] = ibuf[i];
		c++;
		if (c == 3) {
			obuf[j] = bs64_encode_map[(tmp[0] >> 2) & 0x3f];
			j++;
			obuf[j] = bs64_encode_map[((tmp[0] << 4) & 0x30) |
			    ((tmp[1] >> 4) & 0x0f)];
			j++;
			obuf[j] = bs64_encode_map[((tmp[1] << 2) & 0x3c) |
			    ((tmp[2] >> 6) & 0x03)];
			j++;
			obuf[j] = bs64_encode_map[tmp[2] & 0x3f];
			j++;
			c = 0;
		}
	}

	if (c == 1) {
		obuf[j] = bs64_encode_map[(tmp[0] >> 2) & 0x3f];
		j++;
		obuf[j] = bs64_encode_map[((tmp[0] << 4) & 0x30)];
		j++;
		obuf[j] = '=';
		j++;
		obuf[j] = '=';
		j++;
	} else if (c == 2) {
		obuf[j] = bs64_encode_map[(tmp[0] >> 2) & 0x3f];
		j++;
		obuf[j] = bs64_encode_map[((tmp[0] << 4) & 0x30) |
		    ((tmp[1] >> 4) & 0x0f)];
		j++;
		obuf[j] = bs64_encode_map[((tmp[1] << 2) & 0x3c)];
		j++;
		obuf[j] = '=';
		j++;
	}

	obuf[j] = '\0';
}

char *
base64_encode2(const char *ibuf)
{
	char *obuf;
	int i, j = 0, c = 0;
	char tmp[3];

	obuf = malloc((strlen(ibuf) + 2) / 3 * 4 + 1);
	if (obuf == NULL) {
		perror("malloc");
		return NULL;
	}

	for (i = 0; ibuf[i] != '\0'; i++) {
		tmp[c] = ibuf[i];
		c++;
		if (c == 3) {
			obuf[j] = bs64_encode_map[(tmp[0] >> 2) & 0x3f];
			j++;
			obuf[j] = bs64_encode_map[((tmp[0] << 4) & 0x30) |
			    ((tmp[1] >> 4) & 0x0f)];
			j++;
			obuf[j] = bs64_encode_map[((tmp[1] << 2) & 0x3c) |
			    ((tmp[2] >> 6) & 0x03)];
			j++;
			obuf[j] = bs64_encode_map[tmp[2] & 0x3f];
			j++;
			c = 0;
		}
	}

	if (c == 1) {
		obuf[j] = bs64_encode_map[(tmp[0] >> 2) & 0x3f];
		j++;
		obuf[j] = bs64_encode_map[((tmp[0] << 4) & 0x30)];
		j++;
		obuf[j] = '=';
		j++;
		obuf[j] = '=';
		j++;
	} else if (c == 2) {
		obuf[j] = bs64_encode_map[(tmp[0] >> 2) & 0x3f];
		j++;
		obuf[j] = bs64_encode_map[((tmp[0] << 4) & 0x30) |
		    ((tmp[1] >> 4) & 0x0f)];
		j++;
		obuf[j] = bs64_encode_map[((tmp[1] << 2) & 0x3c)];
		j++;
		obuf[j] = '=';
		j++;
	}

	obuf[j] = '\0';
	return obuf;
}

int
base64_decode(const char *ibuf, char *obuf)
{
	unsigned char ch;
	char value;
	unsigned int tmp;
	int i, j = 0, c = 0;

	for (i = 0; ibuf[i] != '\0'; i++) {
		ch = ibuf[i];
		if (ch == '=')
			continue;

		value = bs64_decode_map[ch];
		if (value == -1)
			return -1;

		tmp = (tmp << 6) | value;
		c++;
		if (c == 4) {
			obuf[j] = tmp >> 16 & 0xff;
			j++;
			obuf[j] = tmp >> 8 & 0xff;
			j++;
			obuf[j] = tmp & 0xff;
			j++;
			c = 0;
		}
	}

	if (c == 2) {
		obuf[j] = tmp >> 4 & 0xff;
		j++;
	} else if (c == 3) {
		obuf[j] = tmp >> 10 & 0xff;
		j++;
		obuf[j] = tmp >> 2 & 0xff;
		j++;
	}

	if (j == 0)
		return -1;

	obuf[j] = '\0';
	j++;
	return j;
}

char *
base64_decode2(const char *ibuf)
{
	unsigned char ch;
	char value;
	char *obuf;
	unsigned int tmp;
	int i, j = 0, c = 0;

	if (ibuf[0] == '=')
		return NULL;

	obuf = malloc((strlen(ibuf) + 2) / 3 * 4 + 1);
	if (obuf == NULL) {
		perror("malloc");
		return NULL;
	}

	for (i = 0; ibuf[i] != '\0'; i++) {
		ch = ibuf[i];
		if (ch == '=')
			continue;

		value = bs64_decode_map[ch];
		if (value == -1) {
			free(obuf);
			return NULL;
		}

		tmp = (tmp << 6) | value;
		c++;
		if (c == 4) {
			obuf[j] = tmp >> 16 & 0xff;
			j++;
			obuf[j] = tmp >> 8 & 0xff;
			j++;
			obuf[j] = tmp & 0xff;
			j++;
			c = 0;
		}
	}

	if (c == 2) {
		obuf[j] = tmp >> 4 & 0xff;
		j++;
	} else if (c == 3) {
		obuf[j] = tmp >> 10 & 0xff;
		j++;
		obuf[j] = tmp >> 2 & 0xff;
		j++;
	}

	obuf[j] = '\0';
	j++;
	return obuf;
}
