CC = gcc
CFLAGS = -Wall -Wextra
TARGET = student
OBJS = main.o student.o

$(TARGET): $(OBJS)
	$(CC) $(OBJS) -o $(TARGET)

# Object files
main.o: main.c student.h structure.h
	$(CC) $(CFLAGS) -c main.c

student.o: student.c student.h structure.h
	$(CC) $(CFLAGS) -c student.c