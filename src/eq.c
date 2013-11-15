#include <string.h>
#include "types.h"
#include "cons.h"
#include "eq.h"

int eq(LispObj *obj1, LispObj *obj2)
{
	if (obj1->type != obj2->type)
		return 0;

	switch (obj1->type) {
	case INT:
		return obj1->value.l_int  == obj2->value.l_int;
	case BOOL:
		return obj1->value.l_bool == obj2->value.l_bool;
	case CHAR:
		return obj1->value.l_char == obj2->value.l_char;
	case STRING:
		return strcmp(obj1->value.l_string, obj2->value.l_string) == 0;
	case SYMBOL:
		return strcmp(obj1->value.l_symbol, obj2->value.l_symbol) == 0;
	case CONS:
		return eq(car(obj1), car(obj2)) && eq(cdr(obj1), cdr(obj2));
	case NIL:
		return 1;
	case FUNCTION:
		return obj1->value.l_function == obj2->value.l_function;
	case ERROR:
		return obj1->value.l_err      == obj2->value.l_err;
	}

	return 0;
}
