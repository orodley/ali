#include <stdlib.h>
#include "types.h"

/* Type-related functions */

struct LispObj *make_int(int x)
{
	struct LispObj *num = malloc(sizeof(struct LispObj));

	num->type        = INT;
	num->value.l_int = x;

	return num;
}

struct LispObj *make_string(char *str)
{
	struct LispObj *string = malloc(sizeof(struct LispObj));

	string->type           = STRING;
	string->value.l_string = str;

	return string;
}

struct LispObj *make_symbol(char *str)
{
	struct LispObj *symbol = malloc(sizeof(struct LispObj));

	symbol->type           = SYMBOL;
	symbol->value.l_symbol = str;

	return symbol;
}

struct LispObj *make_error(enum ErrorCode err)
{
	struct LispObj *error = malloc(sizeof(struct LispObj));

	error->type        = ERROR;
	error->value.l_err = err;

	return error;
}

struct LispObj* nil;

struct LispObj *get_nil()
{
	if (nil == NULL) {
		nil = malloc(sizeof(struct LispObj));
		nil->type = NIL;
	}

	return nil;
}

struct LispObj *make_cons(struct Cons *c_cons)
{
	struct LispObj *lo_cons = malloc(sizeof(struct LispObj));

	lo_cons->type         = CONS;
	lo_cons->value.l_cons = c_cons;
}


/* Free the memory allocated for a LispObj, and the object in its value slot.
 * If it is a cons, its car and cdr are recursively freed */
void free_lisp_obj(struct LispObj *obj)
{
	switch (obj->type) {
		case NIL:
			return; /* NIL sticks around */
		case INT:
		case CHAR:
			break;
		case STRING:
			free(obj->value.l_string);
			break;
		case SYMBOL:
			free(obj->value.l_symbol);
			break;
		case CONS:
			free_lisp_obj(obj->value.l_cons->car);
			free_lisp_obj(obj->value.l_cons->cdr);
			break;
	}

	free(obj);
}
