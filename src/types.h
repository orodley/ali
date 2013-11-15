typedef enum LispType
{
	INT,
	BOOL,
	CHAR,
	STRING,
	SYMBOL,
	CONS,
	NIL,
	FUNCTION,
	ERROR,
} LispType;

typedef enum ErrorCode
{
	UNMATCHED_CLOSE_PAREN,
	UNBOUND_VAR,
	NOT_A_FUNCTION,
	WRONG_ARGC,
	NAME_NOT_A_SYMBOL,
	WRONG_TYPE,
} ErrorCode;

struct Env;

typedef struct LispObj *(*BuiltinFunction)(int argc, struct LispObj *argv[],
		struct Env *env);

typedef struct LispObj {
	union {
		int              l_int;
		int              l_bool;
		char             l_char;
		char            *l_string;
		char            *l_symbol;
		struct Cons     *l_cons;
		BuiltinFunction  l_function;
		ErrorCode        l_err;
	} value;

	LispType type;
	int      refc;
} LispObj;

typedef struct Cons {
	LispObj *car;
	LispObj *cdr;
} Cons;

LispObj *make_int(int x);
LispObj *make_bool(int b);
LispObj *make_char(char c);
LispObj *make_string(char *str);
LispObj *make_symbol(char *str);
LispObj *make_symbol_cpy(char *str);
LispObj *make_function(BuiltinFunction func);
LispObj *make_error(ErrorCode err);
LispObj *make_cons(Cons *c_cons);

void add_ref(LispObj *obj);

LispObj *get_nil();
void free_nil();

void always_free_lisp_obj(LispObj *obj);
void free_lisp_obj(LispObj *obj);
