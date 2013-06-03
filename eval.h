/* Associates names to values */
struct Env {
	struct LispObj *key;
	struct LispObj *value;

	struct Env *next;
};

struct LispObj *eval(struct LispObj *sexpr,    struct Env *env);
struct LispObj *lookup(struct LispObj *symbol, struct Env *env);

struct Env *init_env;
