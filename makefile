CC = gcc
CFLAGS = -lgdi32 -pthread -std=c99 -Wall

TARGET = snake

$(TARGET): main.c
	$(CC) $^ -o $@ $(CFLAGS)

clean:
	rm -f *.exe
