#include <stdlib.h>
#include "types.h"

/* Allocate a new Cons, set its car and cdr, and return
 * a pointer to it */
Cons *cons(LispObj *car, LispObj *cdr)
{
	car->refc++;
	cdr->refc++;

	Cons *new_cons = malloc(sizeof(Cons));
	
	new_cons->car = car;
	new_cons->cdr = cdr;

	return new_cons;
}

LispObj *car(LispObj *cons)
{
	return cons->value.l_cons->car;
}

LispObj *cdr(LispObj *cons)
{
	return cons->value.l_cons->cdr;
}

LispObj *caar(LispObj *cons) { return car(car(cons)); }
LispObj *cadr(LispObj *cons) { return car(cdr(cons)); }
LispObj *cdar(LispObj *cons) { return cdr(car(cons)); }
LispObj *cddr(LispObj *cons) { return cdr(cdr(cons)); }
