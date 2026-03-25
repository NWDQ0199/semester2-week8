OBJS=obj/student.o obj/main.o
TARGET=bin/student
INCLUDE=include/student.h include/structure.h

student: $(OBJS)
	gcc $(OBJS) -o $(TARGET)

obj/main.o: src/main.c $(INCLUDE)
	gcc -c src/main.c
	mv main.o obj/main.o

obj/student.o: src/student.c $(INCLUDE)
	gcc -c src/student.c
	mv student.o obj/student.o

clean:
	rm obj/student.o obj/main.o $(TARGET)
	