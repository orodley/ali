CC     = gcc
LD     = $(CC)
CFLAGS = -std=c99 -Wall
OBJS   = src/lexer.o
OBJS  += $(patsubst %.c, %.o, $(wildcard src/*.c))

.PHONY: all
all: ali

debug: CFLAGS += -g
debug: ali

ali: $(OBJS)
	$(LD) -o $@ $^

src/lexer.c: src/lexer.l
	flex -o $@ --header=src/lexer.h $<

clean:
	rm -f src/*.o
	rm -f src/lexer.c src/lexer.h
