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
	struct Token token = get_token();

	if (token.str != NULL) { /* a NULL pointer = EOF */
		switch (token.type) {
			case T_INTEGER: {
				int x;
				sscanf(token.str, "%d", &x);
				return make_int(x);
			}
			case T_STRING: {
				int len = strlen(token.str);

				/* Take a substring of token.str, skipping the first
				 * and last chars */
				char *str = malloc(sizeof(char) * (len - 2));
				strncpy(str, token.str + 1, len - 2);
				*(str + (len - 2)) = '\0';

				return make_string(str);
			}
			case T_SYMBOL: {
				int len = strlen(token.str);

				char *str = malloc(sizeof(char) * len);
				strncpy(str, token.str, len);
				*(str + len) = '\0';

				return make_symbol(str);
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
