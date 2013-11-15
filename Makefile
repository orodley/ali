CC     = gcc
LD     = $(CC)
CFLAGS = -std=c99 -Wall
OBJS   = lexer.o
OBJS  += $(patsubst %.c, %.o, $(wildcard *.c))

.PHONY: all
all: ali

debug: CFLAGS += -g
debug: ali

ali: $(OBJS)
	$(LD) -o $@ $^

lexer.c: lexer.l
	flex -o $@ --header=lexer.h $<

clean:
	rm -f *.o
	rm -f lexer.c lexer.h
