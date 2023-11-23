CC = clang
CFLAGS = -Werror -Wall -Wextra -Wconversion -Wdouble-promotion -Wstrict-prototypes -pedantic
LFLAGS = -lm

EXECS = xd bad_xd

all: $(EXECS)

xd: xd.o
	$(CC) xd.o $(LFLAGS) -o xd

bad_xd: bad_xd.o
	$(CC) bad_xd.o $(LFLAGS) -o bad_xd

xd.o: xd.c
	$(CC) $(CFLAGS) -c xd.c -o xd.o

bad_xd.o: bad_xd.c
	$(CC) $(CFLAGS) -c bad_xd.c -o bad_xd.o

clean:
	rm -rf $(EXECS) *.o

format:
	clang-format -i -style=file *.[ch]

.PHONY: all xd bad_xd clean format
