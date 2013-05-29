/* Lisp printer */

#include <stdio.h>
#include "types.h"

/* Print an object such that reading it will produce the same object */
void prin1(struct LispObj *obj)
{
	char *format;

	switch(obj->type) {
		case INT:
			format = "%d";
			break;
		case STRING:
			format = "\"%s\""; /* TODO: Escape chars */
			break;
		case SYMBOL:
			format = "%s";
			break;
		case CHAR:
			format = "#\\%c";
	}

	printf(format, obj->value);
}
