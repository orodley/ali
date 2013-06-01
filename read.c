/* The Lisp reader */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "types.h"
#include "cons.h"
#include "lexer.h"
#include "read.h"

struct LispObj *read_from_string(char str[])
{
	FILE *stream = fmemopen(str, strlen(str), "r");
	return read_from_stream(stream);
}

struct LispObj *read_from_stream(FILE *stream)
{
	yyin = stream;

	struct Token token;

	if ((token = get_token()).str != NULL) {
		switch (token.type) {
			case T_INTEGER: {
				int x;
				sscanf(token.str, "%d", &x);
				return make_int(x);
			}
		}
	} else {
		return NULL;
	}
}

struct Token get_token()
{
	enum TokenType type = yylex();

	return (struct Token) {
		.str  = type != 0 ? yytext : NULL,
		.type = type
	};
}
