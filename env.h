/* Associates names to values */
struct Env {
	struct LispObj *key;
	struct LispObj *value;

	struct Env *next;
};

struct LispObj *lookup(struct LispObj *symbol, struct Env *env);
