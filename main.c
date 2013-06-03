#include <stdio.h>
#include "read.h"
#include "types.h"
#include "print.h"
#include "lexer.h"

const char PROMPT[] = "> ";
const char RESULT[] = ":";

int main(int argc, char *argv[])
{
	struct LispObj *obj;

	/* Stop yylex() from printing anything */
	yyout = fopen("/dev/null", "r");

	for (;;) {
		fputs(PROMPT, stdout);
		obj = read_from_stream(stdin);

		if (obj == NULL) /* EOF */
			break;

		fputs(RESULT, stdout);
		print(obj);

		free_lisp_obj(obj);
	}

	putchar('\n');
	return 1;
}
