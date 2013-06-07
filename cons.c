#include <stdlib.h>
#include "types.h"

/* Allocate a new Cons, set its car and cdr, and return
 * a pointer to it */
struct Cons *cons(struct LispObj *car, struct LispObj *cdr)
{
	car->refc++;
	cdr->refc++;

	struct Cons *new_cons = malloc(sizeof(struct Cons));
	
	new_cons->car = car;
	new_cons->cdr = cdr;

	return new_cons;
}

struct LispObj *car(struct LispObj *cons)
{
	return cons->value.l_cons->car;
}

struct LispObj *cdr(struct LispObj *cons)
{
	return cons->value.l_cons->cdr;
}

struct LispObj *caar(struct LispObj *cons) { return car(car(cons)); }
struct LispObj *cadr(struct LispObj *cons) { return car(cdr(cons)); }
struct LispObj *cdar(struct LispObj *cons) { return cdr(car(cons)); }
struct LispObj *cddr(struct LispObj *cons) { return cdr(cdr(cons)); }
