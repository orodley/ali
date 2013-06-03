#include "types.h"

struct LispObj *eval(struct LispObj *sexpr)
{
	switch (sexpr->type) {
		/* Self-evaluating types */
		case INT:
		case CHAR:
		case STRING:
		case NIL:
			return sexpr;
		default: /* Placeholder until we can lookup vars */
			return make_error(UNBOUND_VAR);
	}
}
