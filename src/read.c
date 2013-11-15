/* The Lisp reader */

#include <stdlib.h>
#include <string.h>
#include "types.h"
#include "cons.h"
#include "lexer.h"
#include "read.h"
#include "print.h"

LispObj *read_from_string(char *str)
{
	YY_BUFFER_STATE yy_buf = yy_scan_string(str);
	LispObj *obj = read_from_yybuf(yy_buf);
	yy_delete_buffer(yy_buf);

	return obj;
}

LispObj *read_from_stream(FILE *stream)
{
	YY_BUFFER_STATE yy_buf = yy_create_buffer(stream, YY_BUF_SIZE);
	LispObj *obj = read_from_yybuf(yy_buf);
	yy_delete_buffer(yy_buf);

	return obj;
}

LispObj *read_from_yybuf(YY_BUFFER_STATE yy_buf)
{
	yy_switch_to_buffer(yy_buf);
	Token token = get_token();

	if (token.str == NULL) /* a NULL pointer = EOF */
		return NULL;

	switch (token.type) {
	case T_INTEGER: {
		int x;
		sscanf(token.str, "%d", &x);

		free(token.str);
		return make_int(x);
	}
	case T_CHAR: {
		char c = token.str[2]; /* TODO: name-char reading */

		free(token.str);
		return make_char(c);
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
		return make_symbol(token.str);
	}
	case T_OPEN_PAREN: {
		free(token.str);
		LispObj *car = read_from_yybuf(yy_buf);

		if (car == NULL) /* Unmatched open parenthesis */
			return NULL; /* TODO: Error handling/reporting */

		if ((car->type == ERROR) &&
				(car->value.l_err == UNMATCHED_CLOSE_PAREN)) {
			always_free_lisp_obj(car);
			return get_nil();
		}

		Cons *curr_cons = cons(car, get_nil());
		LispObj *list = make_cons(curr_cons);

		for (;;) {
			car = read_from_yybuf(yy_buf);

			if (car == NULL)
				return NULL;
			if ((car->type == ERROR) &&
					(car->value.l_err == UNMATCHED_CLOSE_PAREN)) {
				always_free_lisp_obj(car);
				break;
			}

			curr_cons->cdr = make_cons(cons(car, get_nil()));
			curr_cons = curr_cons->cdr->value.l_cons;
		}

		return list;
	}
	case T_CLOSE_PAREN:
		free(token.str);
		return make_error(UNMATCHED_CLOSE_PAREN);
	}

	return NULL;
}

Token get_token()
{
	char *str = NULL;
	TokenType type = yylex();

	if (type != 0) {
		str = malloc(sizeof(char) * strlen(yytext) + 1);
		strcpy(str, yytext);
	}

	return (Token) {
		.str  = str,
		.type = type
	};
}
