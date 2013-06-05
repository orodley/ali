#include <stdio.h>
#include "types.h"
#include "print.h"
#include "lexer.h"
#include "read.h"
#include "builtins.h"
#include "eval.h"
#include "env.h"

const char PROMPT[] = "> ";
const char RESULT[] = ":";

int main(int argc, char *argv[])
{
	struct LispObj *obj, *value;
	struct Env *init_env = get_init_env();

	/* Stop yylex() from printing anything */
	yyout = fopen("/dev/null", "r");

	for (;;) {
		fputs(PROMPT, stdout);
		obj = read_from_stream(stdin);

		if (obj == NULL) /* EOF */
			break;

		value = eval(obj, init_env);

		fputs(RESULT, stdout);
		print(value);

		free_lisp_obj(obj);
	}

	putchar('\n');

	free_env(init_env);
	free_nil();

	fclose(yyout);

	return 1;
}
