enum LispType { INT, CHAR, STRING, SYMBOL, CONS, NIL, ERROR };
enum ErrorCode
{
	UNMATCHED_CLOSE_PAREN,
	UNBOUND_VAR,
};

struct LispObj {
	union {
		int          l_int;
		char         l_char;
		char        *l_string;
		char        *l_symbol;
		struct Cons *l_cons;
		enum ErrorCode l_err;
	} value;

	enum LispType type;
};

struct Cons {
	struct LispObj *car;
	struct LispObj *cdr;
};

struct LispObj *make_int(int x);
struct LispObj *make_char(char c);
struct LispObj *make_string(char *str);
struct LispObj *make_symbol(char *str);
struct LispObj *make_error(enum ErrorCode err);
struct LispObj *make_cons(struct Cons *c_cons);
struct LispObj *get_nil();

void free_lisp_obj(struct LispObj *obj);
