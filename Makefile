ali: main.o cons.o read.o
	cc -o ali main.o cons.o read.o

main.o: main.c read.h types.h
	cc -c main.c
cons.o: cons.c types.h
	cc -c cons.c
read.o: read.c types.h cons.h read.h
	cc -c read.c

clean:
	rm *.o
