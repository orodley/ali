#include <stdlib.h>
#include "types.h"
#include "eq.h"
#include "eval.h"

struct LispObj *eval(struct LispObj *sexpr, struct Env *env)
{
	switch (sexpr->type) {
		/* Self-evaluating types */
		case INT:
		case CHAR:
		case STRING:
		case NIL:
			return sexpr;
		case SYMBOL: {
			struct LispObj *value = lookup(sexpr, env);
			if (value == NULL)
				return make_error(UNBOUND_VAR);
		}
	}
}

struct LispObj *lookup(struct LispObj *symbol, struct Env *env)
{
	if (env == NULL)
		return NULL;
	else if (eq(symbol, env->key))
		return env->value;
	else
		return lookup(symbol, env->next);
}

struct Env *init_env = NULL;
