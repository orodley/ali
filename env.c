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

	key  ->refc++;
	value->refc++;

	return env;
}

struct Env *extend_func(struct Env *env, char *name, BuiltinFunction func)
{
	return extend(env, make_symbol_cpy(name), make_function(func));
}

void extend_in_place(struct Env *env, struct LispObj *key, struct LispObj *value)
{
	struct Env *new_env = malloc(sizeof(struct Env));
	new_env->key   = env->key;
	new_env->value = env->value;
	new_env->next  = env->next;

	env->key   = key;
	env->value = value;
	env->next  = new_env;

	key  ->refc++;
	value->refc++;
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

void set(struct Env *env, struct LispObj *key, struct LispObj *value)
{
	if (env == NULL)
		return;

	if (eq(key, env->key)) {
		free_lisp_obj(env->value);
		env->value = value;
		value->refc++;
	} else {
		set(env->next, key, value);
	}
}
