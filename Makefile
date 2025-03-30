CC=gcc
CFLAGS=-Wall -Wextra -O2

all: utouch

utouch: utouch.c
	$(CC) $(CFLAGS) utouch.c -o utouch

clean:
	rm -f utouch
