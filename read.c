/* The Lisp reader */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "types.h"
#include "cons.h"
#include "read.h"

struct LispObj *read_from_string(char str[])
{
	FILE *stream = fmemopen(str, strlen(str), "r");
	return read_from_stream(stream);
}

struct LispObj *read_from_stream(FILE *stream)
{
	int x, n;

	if ((n = scanf("%d", &x)) > 0) {
		struct LispObj *num = malloc(sizeof(struct LispObj));

		num->type        = INT;
		num->value.l_int = x;

		return num;
	} else if (n == EOF) {
		return NULL;
	}
}
