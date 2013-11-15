#include <stdlib.h>
#include <string.h>
#include "types.h"
#include "cons.h"

/* Type-related functions */

LispObj *make_int(int x)
{
	LispObj *num = malloc(sizeof(LispObj));

	num->type        = INT;
	num->value.l_int = x;
	num->refc        = 0;

	return num;
}

LispObj *make_bool(int b)
{
	LispObj *bool = malloc(sizeof(LispObj));

	bool->type         = BOOL;
	bool->value.l_bool = (b ? 1 : 0);
	bool->refc         = 0;

	return bool;
}

LispObj *make_char(char c)
{
	LispObj *character = malloc(sizeof(LispObj));

	character->type         = CHAR;
	character->value.l_char = c;
	character->refc         = 0;

	return character;
}

LispObj *make_string(char *str)
{
	LispObj *string = malloc(sizeof(LispObj));

	string->type           = STRING;
	string->value.l_string = str;
	string->refc           = 0;

	return string;
}

LispObj *make_symbol(char *str)
{
	LispObj *symbol = malloc(sizeof(LispObj));

	symbol->type           = SYMBOL;
	symbol->value.l_symbol = str;
	symbol->refc           = 0;

	return symbol;
}

/* KLUDGE: When the symbols in an Env are eventually freed, free_lisp_obj
 * will try to free the memory allocated for the string. If they are
 * statically allocated, this will fail. Since free_lisp_obj has no way
 * of telling whether the string is statically allocated, we need to
 * dynamically allocate them all */
LispObj *make_symbol_cpy(char *str)
{
	int str_len = strlen(str);
	char *str_cpy = malloc(sizeof(char) * str_len + 1);
	strcpy(str_cpy, str);

	return make_symbol(str_cpy);
}

LispObj *make_function(BuiltinFunction func)
{
	LispObj *function = malloc(sizeof(LispObj));

	function->type             = FUNCTION;
	function->value.l_function = func;
	function->refc             = 0;

	return function;
}

LispObj *make_error(ErrorCode err)
{
	LispObj *error = malloc(sizeof(LispObj));

	error->type        = ERROR;
	error->value.l_err = err;
	error->refc        = 0;

	return error;
}

LispObj* nil;

LispObj *get_nil()
{
	if (nil == NULL) {
		nil = malloc(sizeof(LispObj));
		nil->type = NIL;
		nil->refc = 0;
	}

	return nil;
}

/* This should only be called just before the program exits */
void free_nil()
{
	free(nil);
}

LispObj *make_cons(Cons *c_cons)
{
	LispObj *lo_cons = malloc(sizeof(LispObj));

	lo_cons->type         = CONS;
	lo_cons->value.l_cons = c_cons;
	lo_cons->refc         = 0;

	return lo_cons;
}

void add_ref(LispObj *obj)
{
	switch (obj->type) {
		case INT:
		case BOOL:
		case CHAR:
		case STRING:
		case SYMBOL:
		case FUNCTION:
		case ERROR:
			obj->refc++;
			break;
		case CONS:
			obj->refc++;
			add_ref(car(obj));
			add_ref(cdr(obj));
			break;
		case NIL:
			break;
	}
}

/* Free the memory allocated for a LispObj, and the object in its value slot.
 * If it is a cons, its car and cdr are recursively freed */
void free_lisp_obj(LispObj *obj)
{
	if ((--obj->refc <= 0) && (obj->type != NIL))
		always_free_lisp_obj(obj);
}

void always_free_lisp_obj(LispObj *obj)
{
	switch (obj->type) {
		case NIL:
			return; /* NIL sticks around */
		case INT:
		case BOOL:
		case CHAR:
		case ERROR:
		case FUNCTION:
			break;
		case STRING:
			free(obj->value.l_string);
			break;
		case SYMBOL:
			free(obj->value.l_symbol);
			break;
		case CONS:
			free_lisp_obj(car(obj));
			free_lisp_obj(cdr(obj));
			free(obj->value.l_cons);
			break;
	}

	free(obj);
}
