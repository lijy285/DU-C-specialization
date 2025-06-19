cc = gcc
CFLAGS = -Wall -Wextra -std=gnu99
TARGET = breaker

all: $(TARGET)

$(TARGET): breaker.c
	$(cc) $(CFLAGS) -o $(TARGET) breaker.c
clean:
	rm -f $(TARGET)
	rm -f *~
.PHONY: all clean
