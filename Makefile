CC = gcc
CFLAGS = -Wall

all: bs64encode bs64decode

bs64encode: bs64.c
	$(CC) $(CFLAGS) bs64encode.c $^ -o $@ 

bs64decode: bs64.c
	$(CC) $(CFLAGS) bs64decode.c $^ -o $@ 

.PHONY: clean
clean:
	rm -f bs64encode bs64decode
