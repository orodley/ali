#define BUILTIN_FUNCTION(name) \
	struct LispObj *name(int argc, struct LispObj *argv[], struct Env *env)

struct Env *get_init_env();
