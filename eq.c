#include <string.h>
#include "types.h"

int eq(struct LispObj *obj1, struct LispObj *obj2)
{
	if (obj1->type != obj2->type)
		return 0;

	switch (obj1->type) {
		case INT:
			return obj1->value.l_int  == obj2->value.l_int;
		case CHAR:
			return obj1->value.l_char == obj2->value.l_char;
		case STRING:
			return strcmp(obj1->value.l_string, obj2->value.l_string) == 0;
		case SYMBOL:
			return strcmp(obj1->value.l_symbol, obj2->value.l_symbol) == 0;
	}
}
