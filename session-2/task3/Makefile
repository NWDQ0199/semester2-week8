CC = gcc
CFLAGS = -Wall -Wextra
TARGET = student
OBJS = main.o student.o
DFLAGS = -g -fanalyzer#e.g. stuff like -fanalyzer
FLAGS =#so custom flags can be added with make FLAGS="-Wall" for example
CC+=$(FLAGS)

$(TARGET): $(OBJS)
	$(CC) $(OBJS) -o $(TARGET)


main.o: main.c student.h structure.h
	$(CC) $(CFLAGS) -c main.c

student.o: student.c student.h structure.h
	$(CC) $(CFLAGS) -c student.c

#make clean
clean:
	rm -f $(OBJS) $(TARGET)

all: $(TARGET)

#adds the flags to the compiler
debug: CC+=$(DFLAGS)
debug: $(TARGET)

