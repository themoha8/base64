#ifndef BS64_H_SENRY
#define BS64_H_SENRY

void base64_encode(const char *ibuf, char *obuf);
char *base64_encode2(const char *ibuf);
int base64_decode(const char *ibuf, char *obuf);
char *base64_decode2(const char *ibuf);

#endif
