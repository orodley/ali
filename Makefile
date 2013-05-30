ali: main.o cons.o read.o print.o types.o
	cc -o ali main.o cons.o read.o print.o types.o

main.o:  main.c read.h types.h
	cc -c main.c
cons.o:  cons.c types.h
	cc -c cons.c
read.o:  read.c types.h cons.h read.h
	cc -c read.c
print.o: print.c types.h
	cc -c print.c
types.o: types.c types.h
	cc -c types.c

clean:
	rm *.o
