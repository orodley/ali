#include <stdio.h>
#include "read.h"
#include "types.h"
#include "print.h"

const char PROMPT[] = "> ";
const char RESULT[] = ": ";

int main(int argc, char *argv[])
{
	struct LispObj *obj;

	for (;;) {
		fputs(PROMPT, stdout);
		obj = read_from_stream(stdin);

		if (obj == NULL) /* EOF */
			break;

		fputs(RESULT, stdout);
		prin1(obj);
		putchar('\n');
	}

	return 1;
}
