/* Associates names to values */
struct Env {
	struct LispObj *key;
	struct LispObj *value;

	struct Env *next;
};

struct LispObj *lookup(struct LispObj *symbol, struct Env *env);
struct Env *extend(struct Env *env, struct LispObj *key, struct LispObj *value);
void free_env(struct Env *env);
