CC = gcc
CFLAGS = -pthread

TARGET = library_system

SRC = main.c book_operations.c thread_manager.c
OBJ = main.o book_operations.o thread_manager.o

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJ)

main.o: main.c
	$(CC) $(CFLAGS) -c main.c

book_operations.o: book_operations.c
	$(CC) $(CFLAGS) -c book_operations.c

thread_manager.o: thread_manager.c
	$(CC) $(CFLAGS) -c thread_manager.c

clean:
	rm -f $(OBJ) $(TARGET)
