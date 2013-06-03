/* The Lisp reader */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "types.h"
#include "cons.h"
#include "lexer.h"
#include "print.h"
#include "read.h"

struct LispObj *read_from_string(char *str)
{
	YY_BUFFER_STATE yy_buf = yy_scan_string(str);
	struct LispObj *obj = read_from_yybuf(yy_buf);
	yy_delete_buffer(yy_buf);

	return obj;
}

struct LispObj *read_from_stream(FILE *stream)
{
	YY_BUFFER_STATE yy_buf = yy_create_buffer(stream, YY_BUF_SIZE);
	struct LispObj *obj = read_from_yybuf(yy_buf);
	yy_delete_buffer(yy_buf);

	return obj;
}

struct LispObj *read_from_yybuf(YY_BUFFER_STATE yy_buf)
{
	yy_switch_to_buffer(yy_buf);
	struct Token token = get_token();

	if (token.str != NULL) { /* a NULL pointer = EOF */
		switch (token.type) {
			case T_INTEGER: {
				int x;
				sscanf(token.str, "%d", &x);

				free(token.str);
				return make_int(x);
			}
			case T_STRING: {
				int len = strlen(token.str);

				/* Take a substring of token.str, skipping the first
				 * and last chars */
				char *str = malloc(sizeof(char) * (len - 2));
				strncpy(str, token.str + 1, len - 2);
				*(str + (len - 2)) = '\0';

				free(token.str);
				return make_string(str);
			}
			case T_SYMBOL: {
				int len = strlen(token.str);

				char *str = malloc(sizeof(char) * len);
				strncpy(str, token.str, len);
				*(str + len) = '\0';

				free(token.str);
				return make_symbol(str);
			}
			case T_OPEN_PAREN: {
				struct Token car = get_token();

				if (car.str == NULL) /* Unmatched open parenthesis */
					return NULL;     /* TODO: Error handling/reporting */

				if (car.type == T_CLOSE_PAREN)
					return get_nil();

				struct LispObj *first_obj = read_from_string(car.str);
				yy_switch_to_buffer(yy_buf); /* Switch back to the buffer */

				struct Cons *curr_cons = cons(first_obj, get_nil());
				struct LispObj *list = make_cons(curr_cons);

				while ((car = get_token()).type != T_CLOSE_PAREN) {
					if (car.str == NULL)
						return NULL;

					first_obj = read_from_string(car.str);
					yy_switch_to_buffer(yy_buf);

					curr_cons->cdr = make_cons(cons(first_obj, get_nil()));
					curr_cons = curr_cons->cdr->value.l_cons;
				}

				return list;
			}
		}
	} else {
		return NULL;
	}
}

struct Token get_token()
{
	char *str = NULL;
	enum TokenType type = yylex();

	if (type != 0) {
		str = malloc(sizeof(char) * strlen(yytext));
		strcpy(str, yytext);
	}

	return (struct Token) {
		.str  = str,
		.type = type
	};
}
