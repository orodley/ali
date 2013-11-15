#include <stdlib.h>
#include "types.h"
#include "eq.h"
#include "env.h"

LispObj *lookup(LispObj *symbol, Env *env)
{
	if (env == NULL)
		return NULL;
	else if (eq(symbol, env->key))
		return env->value;
	else
		return lookup(symbol, env->next);
}

Env *extend(Env *env, LispObj *key, LispObj *value)
{
	Env *prev_env = env;
	env = malloc(sizeof(Env));

	env->key   = key;
	env->value = value;
	env->next  = prev_env;

	key  ->refc++;
	value->refc++;

	return env;
}

Env *extend_func(Env *env, char *name, BuiltinFunction func)
{
	return extend(env, make_symbol_cpy(name), make_function(func));
}

void extend_in_place(Env *env, LispObj *key, LispObj *value)
{
	Env *new_env = malloc(sizeof(Env));
	new_env->key   = env->key;
	new_env->value = env->value;
	new_env->next  = env->next;

	env->key   = key;
	env->value = value;
	env->next  = new_env;

	key  ->refc++;
	value->refc++;
}

void free_env(Env *env)
{
	if (env == NULL)
		return;

	free_lisp_obj(env->key);
	free_lisp_obj(env->value);

	Env *next = env->next;
	free(env);
	free_env(next); /* Call free_env last to make it tail-recursive */
}

void set(Env *env, LispObj *key, LispObj *value)
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
