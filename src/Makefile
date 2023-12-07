CC = gcc
CFLAGS = -Wall -Wextra -g
TARGET = main
SRC = main.c utils.c

$(TARGET): $(SRC:.c=.o)
    $(CC) $(CFLAGS) $^ -o $@

clean:
    rm -f $(TARGET) $(SRC:.c=.o)
