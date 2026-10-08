CC = gcc
CFLAGS = -Wall -Wextra -Iinclude

TARGET = schedsim

SRC = src/main.c src/process.c src/scheduler.c

$(TARGET): $(SRC)
	$(CC) $(CFLAGS) $(SRC) -o $(TARGET)

clean:
	rm -f $(TARGET)