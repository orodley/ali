#include <stdlib.h>
#include <string.h>
#include "types.h"
#include "cons.h"
#include "eq.h"
#include "builtins.h"
#include "env.h"
#include "eval.h"

struct LispObj *eval(struct LispObj *sexpr, struct Env *env)
{
	switch (sexpr->type) {
		/* Self-evaluating types */
		case INT:
		case CHAR:
		case STRING:
		case FUNCTION:
		case NIL:
			return sexpr;
		case SYMBOL: {
			struct LispObj *value = lookup(sexpr, env);
			if (value == NULL)
				return make_error(UNBOUND_VAR);
			else
				return value;
		}
		case CONS: {
			struct LispObj *result = eval_special_form(sexpr, env);
			if (result != NULL) /* It was a special form */
				return result;

			struct LispObj *func = eval(car(sexpr), env);

			if (func->type == ERROR)
				return func;
			if (func->type != FUNCTION)
				return make_error(NOT_A_FUNCTION);

			int argc = 0;
			struct LispObj *s = sexpr;
			for (; cdr(s)->type != NIL; argc++)
				s = cdr(s);

			struct LispObj **args = malloc(sizeof(struct LispObj*) * argc);
			for (int i = 0; i < argc; i++) {
				sexpr = cdr(sexpr);
				args[i] = eval(car(sexpr), env);
			}

			result = func->value.l_function(argc, args);
			free(args);
			return result;
		}
	}
}

struct LispObj *eval_special_form(struct LispObj *sexpr, struct Env *env)
{
	char *name = car(sexpr)->value.l_symbol;

	if (strcmp(name, "quote") == 0) {
		return cadr(sexpr);
	} else if (strcmp(name, "if") == 0) {
		struct LispObj *f         = make_bool(0);
		struct LispObj *condition = eval(cadr(sexpr), env);

		struct LispObj *result_form;
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
