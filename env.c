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

struct Env *extend(struct Env *env, struct LispObj *key, struct LispObj *value)
{
	struct Env *prev_env = env;
	env = malloc(sizeof(struct Env));

	env->key   = key;
	env->value = value;
	env->next  = prev_env;

	return env;
}
