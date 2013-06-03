CFLAGS =

ifdef DEBUG
	CFLAGS+=-g
endif

ali: main.o cons.o read.o print.o types.o lexer.o
	cc $(CFLAGS) -o ali main.o cons.o read.o print.o types.o lexer.o

main.o:  main.c read.h types.h lexer.h
	cc $(CFLAGS) -c main.c
cons.o:  cons.c types.h
	cc $(CFLAGS) -c cons.c
read.o:  read.c types.h cons.h read.h lexer.h
	cc $(CFLAGS) -c read.c
print.o: print.c types.h
	cc $(CFLAGS) -c print.c
types.o: types.c types.h
	cc $(CFLAGS) -c types.c
lexer.o: lexer.c
	cc $(CFLAGS) -c lexer.c
lexer.h: lexer.c
lexer.c: lexer.l
	flex -o lexer.c --header=lexer.h lexer.l

clean:
	rm *.o
	rm lexer.c
	rm lexer.h
