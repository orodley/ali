#include <stdio.h>
#include "types.h"
#include "print.h"
#include "lexer.h"
#include "read.h"
#include "builtins.h"
#include "eval.h"

const char PROMPT[] = "> ";
const char RESULT[] = ":";

int main(int argc, char *argv[])
{
	LispObj *obj, *value;
	Env *init_env = get_init_env();

	/* Stop yylex() from printing anything */
	yyout = fopen("/dev/null", "r");

	for (;;) {
		fputs(PROMPT, stdout);
		obj = read_from_stream(stdin);

		if (obj == NULL) /* EOF */
			break;

		add_ref(obj);

		value = eval(obj, init_env);
		add_ref(value);
		free_lisp_obj(obj);

		fputs(RESULT, stdout);
		print(value);
		free_lisp_obj(value);
	}

	putchar('\n');

	yylex_destroy();
	free_env(init_env);
	free_nil();

	fclose(yyout);

	return 0;
}
