#include <stdio.h>
#include <stdlib.h>
#include "types.h"
#include "env.h"
#include "builtins.h"

BUILTIN_FUNCTION(b_plus)
{
	int result = 0;

	for (int i = 0; i < argc; i++) {
		result += argv[i]->value.l_int;
	}

	return make_int(result);
}

BUILTIN_FUNCTION(b_minus)
{
	if (argc == 0)
		return make_error(WRONG_ARGC);
	if (argc == 1)
		return make_int(-argv[0]->value.l_int);
	
	int result = argv[0]->value.l_int;

	for (int i = 1; i < argc; i++)
		result -= argv[i]->value.l_int;

	return make_int(result);
}

BUILTIN_FUNCTION(b_multiply)
{
	int result = 1;

	for (int i = 0; i < argc; i++) {
		result *= argv[i]->value.l_int;
	}

	return make_int(result);
}

static char *names[] = {
	"+",    "-",     "*"
};
static BuiltinFunction functions[] = {
	b_plus, b_minus, b_multiply
};

struct Env *get_init_env()
{
	struct Env *init_env, *prev_env = NULL;
	int num_builtins = (sizeof(names) / sizeof(*names));

	for (int i = 0; i < num_builtins; i++) {
		prev_env = init_env;
		init_env = malloc(sizeof(struct Env));

		init_env->key   = make_symbol(names[i]);
		init_env->value = make_function(functions[i]);
		init_env->next  = prev_env;
	}

	prev_env = init_env;
	init_env = malloc(sizeof(struct Env));

	init_env->key   = make_symbol("t");
	init_env->value = make_bool(1);
	init_env->next  = prev_env;

	prev_env = init_env;
	init_env = malloc(sizeof(struct Env));

	init_env->key   = make_symbol("f");
	init_env->value = make_bool(0);
	init_env->next  = prev_env;

	return init_env;
}
