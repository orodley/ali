#include <stdlib.h>
#include "types.h"

/* Allocate a new Cons, set its car and cdr, and return
 * a pointer to it */
struct Cons *cons(struct LispObj *car, struct LispObj *cdr)
{
	struct Cons *new_cons = malloc(sizeof(struct Cons));
	
	new_cons->car = car;
	new_cons->cdr = cdr;

	return new_cons;
}
