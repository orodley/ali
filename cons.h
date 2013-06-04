struct Cons *cons(struct LispObj *car, struct LispObj *cdr);
struct LispObj *car (struct LispObj *cons);
struct LispObj *cdr (struct LispObj *cons);
struct LispObj *caar(struct LispObj *cons);
struct LispObj *cadr(struct LispObj *cons);
struct LispObj *cdar(struct LispObj *cons);
struct LispObj *cddr(struct LispObj *cons);
