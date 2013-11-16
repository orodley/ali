#include <stdio.h>
#include <stdlib.h>
#include "types.h"
#include "cons.h"
#include "builtins.h"

BUILTIN_FUNCTION(b_plus)
{
	int result = 0;

	for (int i = 0; i < argc; i++) {
		if (argv[i]->type != INT)
			return make_error(WRONG_TYPE);

		result += argv[i]->value.l_int;
	}

	return make_int(result);
}

BUILTIN_FUNCTION(b_minus)
{
	if (argc == 0)
		return make_error(WRONG_ARGC);
	if (argv[0]->type != INT)
		return make_error(WRONG_TYPE);
	if (argc == 1)
		return make_int(-argv[0]->value.l_int);

	int result = argv[0]->value.l_int;

	for (int i = 1; i < argc; i++) {
		if (argv[i]->type != INT)
			return make_error(WRONG_TYPE);

		result -= argv[i]->value.l_int;
	}

	return make_int(result);
}

BUILTIN_FUNCTION(b_multiply)
{
	int result = 1;

	for (int i = 0; i < argc; i++) {
		if (argv[i]->type != INT)
			return make_error(WRONG_TYPE);

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
	if (argv[0]->type != CONS)
		return make_error(WRONG_TYPE);

	return car(argv[0]);
}

BUILTIN_FUNCTION(b_cdr)
{
	if (argc != 1)
		return make_error(WRONG_ARGC);
	if (argv[0]->type != CONS)
		return make_error(WRONG_TYPE);

	return cdr(argv[0]);
}

BUILTIN_FUNCTION(b_set)
{
	if (argc != 2)
		return make_error(WRONG_ARGC);
	if (argv[0]->type != SYMBOL)
		return make_error(NAME_NOT_A_SYMBOL);

	set(env, argv[0], argv[1]);
	return argv[1];
}

BUILTIN_FUNCTION(b_def)
{
	if (argc != 2)
		return make_error(WRONG_ARGC);
	if (argv[0]->type != SYMBOL)
		return make_error(NAME_NOT_A_SYMBOL);

	LispObj *name_sym = argv[0];
	LispObj *value    = argv[1];

	if (lookup(name_sym, env) != NULL)
		return make_error(REDEFINITION);

	extend_in_place(env, name_sym, value);
	return name_sym;
}

Env *get_init_env()
{
	Env *env = NULL;

	/* Builtin functions */
	env = extend_func(env, "+",    b_plus);
	env = extend_func(env, "-",    b_minus);
	env = extend_func(env, "*",    b_multiply);
	env = extend_func(env, "cons", b_cons);
	env = extend_func(env, "car",  b_car);
	env = extend_func(env, "cdr",  b_cdr);
	env = extend_func(env, "set",  b_set);
	env = extend_func(env, "def",  b_def);

	/* Boolean values */
	env = extend(env, make_symbol_cpy("t"), make_bool(1));
	env = extend(env, make_symbol_cpy("f"), make_bool(0));

	return env;
}
