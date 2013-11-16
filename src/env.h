/* Associates names to values */
typedef struct Env {
	LispObj *key;
	LispObj *value;

	struct Env *next;
} Env;

LispObj *lookup(LispObj *symbol, Env *env);
Env *extend(Env *env, LispObj *key, LispObj *value);
void extend_in_place(Env *env, LispObj *key, LispObj *value);
Env *extend_func(Env *env, char *name, BuiltinFunction func);
void free_env(Env *env);
void set(Env *env, LispObj *key, LispObj *value);
void print_env(Env *env);
