/* Associates names to values */
struct Env {
	struct LispObj *key;
	struct LispObj *value;

	struct Env *next;
};

#define BUILTIN_FUNCTION(name) \
	struct LispObj *name(int argc, struct LispObj *argv[])

struct Env *get_init_env();
