# compiler settings
CC = gcc
CFLAGS = -std=c11 -pedantic -Wall -Werror -D_XOPEN_SOURCE=700

.PHONY: all clean

all: clash

clean:
	rm -f clash

clash: clash.c --plist.o
	$(CC) $(CFLAGS) -o *.o clash.c 

# Helper targets -- makes it mostly somewhat private
--plist.o:
	$(CC) $(CFLAGS) -c plist.c plist.h