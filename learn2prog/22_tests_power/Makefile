CC = gcc
CFLAGS = -Wall -Werror -std=gnu99

all: test-power

power.o: power.c
	$(CC) $(CFLAGS) -c power.c

test-power.o: test-power.c
	$(CC) $(CFLAGS) -c test-power.c

test-power: test-power.o power.o
	$(CC) $(CFLAGS) -o test-power test-power.o power.o

clean:
	rm -f *.o test-power
