#include <stdlib.h>
#include <string.h>
#include "types.h"
#include "eq.h"
#include "builtins.h"
#include "env.h"
#include "eval.h"

struct LispObj *eval(struct LispObj *sexpr, struct Env *env)
{
	switch (sexpr->type) {
		/* Self-evaluating types */
		case INT:
		case CHAR:
		case STRING:
		case FUNCTION:
		case NIL:
			return sexpr;
		case SYMBOL: {
			struct LispObj *value = lookup(sexpr, env);
			if (value == NULL)
				return make_error(UNBOUND_VAR);
			else
				return value;
		}
		case CONS: {
			struct LispObj *result = eval_special_form(sexpr, env);
			if (result != NULL) /* It was a special form */
				return result;

			struct LispObj *func = eval(sexpr->value.l_cons->car, env);

			if (func->type == ERROR)
				return func;
			if (func->type != FUNCTION)
				return make_error(NOT_A_FUNCTION);

			int argc = 0;
			struct LispObj *s = sexpr;
			for (; s->value.l_cons->cdr->type != NIL; argc++)
				s = s->value.l_cons->cdr;

			struct LispObj **args = malloc(sizeof(struct LispObj*) * argc);
			for (int i = 0; i < argc; i++) {
				sexpr = sexpr->value.l_cons->cdr;
				args[i] = eval(sexpr->value.l_cons->car, env);
			}

			result = func->value.l_function(argc, args);
			free(args);
			return result;
		}
	}
}

struct LispObj *eval_special_form(struct LispObj *sexpr, struct Env *env)
{
	char *name = sexpr->value.l_cons->car->value.l_symbol;

	if (strcmp(name, "quote") == 0) {
		/* Return the CADR of the form */
		return sexpr->value.l_cons->cdr->value.l_cons->car;
	}

	return NULL; /* NULL signifies that it didn't match any special form */
}
