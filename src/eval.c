#include <stdlib.h>
#include <string.h>
#include "types.h"
#include "cons.h"
#include "eq.h"
#include "builtins.h"
#include "eval.h"

LispObj *eval(LispObj *sexpr, Env *env)
{
	switch (sexpr->type) {
	/* Self-evaluating types */
	case INT:
	case BOOL:
	case CHAR:
	case STRING:
	case FUNCTION:
	case NIL:
	case ERROR:
		return sexpr;
	case SYMBOL: {
		LispObj *value = lookup(sexpr, env);
		if (value == NULL)
			return make_error(UNBOUND_VAR);
		else
			return value;
	}
	case CONS: {
		LispObj *result = eval_special_form(sexpr, env);
		if (result != NULL) /* It was a special form */
			return result;

		LispObj *func = eval(car(sexpr), env);

		if (func->type == ERROR)
			return func;
		if (func->type != FUNCTION)
			return make_error(NOT_A_FUNCTION);

		int argc = 0;
		LispObj *s = sexpr;
		for (; cdr(s)->type != NIL; argc++)
			s = cdr(s);

		LispObj **args = malloc(sizeof(LispObj*) * argc);
		for (int i = 0; i < argc; i++) {
			sexpr = cdr(sexpr);

			LispObj *arg = eval(car(sexpr), env);
			if (arg->type == ERROR) {
				result = arg; /* Propagate errors */
				goto cleanup;
			}

			args[i] = arg;
		}

		result = func->value.l_function(argc, args, env);

cleanup:
		/* We have to free all of the arguments to the function, but
		 * result might be/depend on one of them, so increment refc
		 * first, and then remove it afterwards */
		add_ref(result);
		for (int i = 0; i < argc; i++)
			free_lisp_obj(args[i]);
		result->refc--;

		free(args);
		return result;
	}
	}

	return NULL;
}

LispObj *eval_special_form(LispObj *sexpr, Env *env)
{
	if (car(sexpr)->type != SYMBOL)
		return NULL;

	char *name = car(sexpr)->value.l_symbol;

	if (strcmp(name, "quote") == 0) {
		return cadr(sexpr);
	} else if (strcmp(name, "if") == 0) {
		LispObj *f         = make_bool(0);
		LispObj *condition = eval(cadr(sexpr), env);

		LispObj *result_form;
		if (eq(f, condition))
			result_form = cadr(cddr(sexpr)); /* false */
		else
			result_form = cadr(cdr(sexpr));  /* true */

		free_lisp_obj(f);
		free_lisp_obj(condition);

		return eval(result_form, env);
	} else if (strcmp(name, "define") == 0) {
		if (cadr(sexpr)->type != SYMBOL)
			return make_error(NAME_NOT_A_SYMBOL);

		extend_in_place(env, cadr(sexpr), eval(car(cddr(sexpr)), env));
		return cadr(sexpr);
	}

	return NULL; /* NULL signifies that it didn't match any special form */
}
