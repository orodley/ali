enum LispType { INT, BOOL, CHAR, STRING, SYMBOL, CONS, NIL, FUNCTION, ERROR };
enum ErrorCode
{
	UNMATCHED_CLOSE_PAREN,
	UNBOUND_VAR,
	NOT_A_FUNCTION,
	WRONG_ARGC,
};

typedef struct LispObj *(*BuiltinFunction)(int argc, struct LispObj *argv[]);

struct LispObj {
	union {
		int               l_int;
		int               l_bool;
		char              l_char;
		char             *l_string;
		char             *l_symbol;
		struct Cons      *l_cons;
		BuiltinFunction   l_function;
		enum ErrorCode    l_err;
	} value;

	enum LispType type;
};

struct Cons {
	struct LispObj *car;
	struct LispObj *cdr;
};

struct LispObj *make_int(int x);
struct LispObj *make_bool(int b);
struct LispObj *make_char(char c);
struct LispObj *make_string(char *str);
struct LispObj *make_symbol(char *str);
struct LispObj *make_symbol_cpy(char *str);
struct LispObj *make_function(BuiltinFunction func);
struct LispObj *make_error(enum ErrorCode err);
struct LispObj *make_cons(struct Cons *c_cons);

struct LispObj *get_nil();
void free_nil();

void free_lisp_obj(struct LispObj *obj);
