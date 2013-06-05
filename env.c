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

void free_env(struct Env *env)
{
	if (env == NULL)
		return;

	free_lisp_obj(env->key);
	free_lisp_obj(env->value);

	struct Env *next = env->next;
	free(env);
	free_env(next); /* Call free_env last to make it tail-recursive */
}
