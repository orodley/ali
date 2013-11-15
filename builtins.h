#include "env.h"

#define BUILTIN_FUNCTION(name) \
	struct LispObj *name(int argc, struct LispObj *argv[], struct Env *env)

Env *get_init_env();
