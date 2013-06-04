/* Lisp printer */

#include <stdio.h>
#include "types.h"
#include "print.h"

/* Print an object such that reading it will produce the same object */
void prin1(struct LispObj *obj)
{
	switch(obj->type) {
		case INT:
			printf("%d",     obj->value.l_int);
			break;
		case BOOL:
			putchar(obj->value.l_int ? 't' : 'f');
			break;
		case STRING:
			printf("\"%s\"", obj->value.l_string); /* TODO: Escape chars */
			break;
		case SYMBOL:
			printf("%s",     obj->value.l_symbol);
			break;
		case CHAR:
			printf("#\\%c",  obj->value.l_char);
			break;
		case FUNCTION:
			printf("#<function object at %p>", obj->value.l_function);
			break;
		case CONS: {
			struct Cons *cons = obj->value.l_cons;
			putchar('(');
			prin1(cons->car);

			for (;;) {
				enum LispType type = cons->cdr->type;

				if (type == NIL)
					break;
				if (type != CONS) {
					fputs(" . ", stdout);
					prin1(cons->cdr);
					break;
				}

				cons = cons->cdr->value.l_cons;
				putchar(' ');
				prin1(cons->car);
			}

			putchar(')');
			break;
		}
		case NIL:
			fputs("()", stdout);
			break;
		case ERROR:
			print_error(obj->value.l_err);
	}
}

/* TODO: Better error reporting, e.g. rather than just printing "Unbound
 * variable", tell the user *which* variable is unbound */
void print_error(enum ErrorCode err)
{
	fputs("ERROR: ", stdout);
	switch (err) {
		case UNMATCHED_CLOSE_PAREN:
			fputs("Unmatched close parenthesis.", stdout);
			break;
		case UNBOUND_VAR:
			fputs("Unbound variable.", stdout);
			break;
		case NOT_A_FUNCTION:
			fputs("Non-function found where a function was expected", stdout);
			break;
		case WRONG_ARGC:
			fputs("Wrong number of arguments", stdout);
			break;
	}
}

/* Like prin1, but preceded by a space and followed by a newline */
void print(struct LispObj *obj)
{
	putchar(' ');
	prin1(obj);
	putchar('\n');
}
