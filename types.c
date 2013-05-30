#include <stdlib.h>
#include "types.h"

/* Type-related functions */

/* Free the memory allocated for a LispObj, and the object in its value slot.
 * If it is a cons, its car and cdr are recursively freed */
void free_lisp_obj(struct LispObj *obj)
{
	switch (obj->type) {
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
