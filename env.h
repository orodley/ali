/* Associates names to values */
struct Env {
	struct LispObj *key;
	struct LispObj *value;

	struct Env *next;
};

struct LispObj *lookup(struct LispObj *symbol, struct Env *env);
struct Env *extend(struct Env *env, struct LispObj *key, struct LispObj *value);
void extend_in_place(struct Env *env, struct LispObj *key, struct LispObj *value);
struct Env *extend_func(struct Env *env, char *name, BuiltinFunction func);
void free_env(struct Env *env);
void set(struct Env *env, struct LispObj *key, struct LispObj *value);
