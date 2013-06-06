#include <stdio.h>
#include <stdlib.h>
#include "types.h"
#include "cons.h"
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

BUILTIN_FUNCTION(b_cons)
{
	if (argc != 2)
		return make_error(WRONG_ARGC);

	return make_cons(cons(argv[0], argv[1]));
}

BUILTIN_FUNCTION(b_car)
{
	if (argc != 1)
		return make_error(WRONG_ARGC);

	return car(argv[0]);
}

BUILTIN_FUNCTION(b_cdr)
{
	if (argc != 1)
		return make_error(WRONG_ARGC);

	return cdr(argv[0]);
}

struct Env *get_init_env()
{
	struct Env *env = NULL;

	/* Builtin functions */
	env = extend_func(env, "+",    b_plus);
	env = extend_func(env, "-",    b_minus);
	env = extend_func(env, "*",    b_multiply);
	env = extend_func(env, "cons", b_cons);
	env = extend_func(env, "car",  b_car);
	env = extend_func(env, "cdr",  b_cdr);

	/* Boolean values */
	env = extend(env, make_symbol_cpy("t"), make_bool(1));
	env = extend(env, make_symbol_cpy("f"), make_bool(0));

	return env;
}
