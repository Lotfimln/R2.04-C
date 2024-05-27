# Variables
CC = gcc
CFLAGS = -Wall -Wextra -Werror
TARGET = main

# Default target
all: $(TARGET)

# Build the target
$(TARGET): main.o
	$(CC) $(CFLAGS) -o $(TARGET) main.o

# Compile main.c to main.o
main.o: main.c
	$(CC) $(CFLAGS) -c main.c -o main.o

# Clean up build files
clean:
	rm -f $(TARGET) *.o

# Phony targets
.PHONY: all clean
