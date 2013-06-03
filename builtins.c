#include <stdio.h>
#include <stdlib.h>
#include "types.h"
#include "builtins.h"

BUILTIN_FUNCTION(b_plus)
{
	int result = 0;

	for(int i = 0; i < argc; i++) {
		result += argv[i]->value.l_int;
	}

	return make_int(result);
}

static char *names[] = {
	"+"
};

static BuiltinFunction functions[] = {
	b_plus
};

struct Env *get_init_env()
{
	struct Env *init_env = NULL;
	int num_builtins = sizeof(names) / sizeof(*names);

	for(int i = 0; i < num_builtins; i++) {
		struct Env *prev_env = init_env;
		init_env = malloc(sizeof(struct Env));

		init_env->key   = make_symbol(names[i]);
		init_env->value = make_function(functions[i]);
		init_env->next = prev_env;
	}

	return init_env;
}
