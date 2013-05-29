#include <stdio.h>
#include "read.h"
#include "types.h"
#include "print.h"

int main(int argc, char *argv[])
{
	prin1(read_from_stream(stdin));
	putchar('\n');

	return 1;
}
