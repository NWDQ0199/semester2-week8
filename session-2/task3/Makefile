
student: student.o main.o
	gcc student.o main.o -o student

main.o: main.c student.h structure.h
	gcc -c main.c

student.o: student.c student.h structure.h
	gcc -c student.c

clean:
	rm student.o main.o student
	