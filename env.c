#include <stdlib.h>
#include "types.h"
#include "eq.h"
#include "env.h"

struct LispObj *lookup(struct LispObj *symbol, struct Env *env)
{
	if (env == NULL)
		return NULL;
	else if (eq(symbol, env->key))
		return env->value;
	else
		return lookup(symbol, env->next);
}
