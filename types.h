enum LispType { INT, CHAR, STRING, SYMBOL, CONS };

struct LispObj {
	union {
		int          l_int;
		char         l_char;
		char        *l_string;
		char        *l_symbol;
		struct Cons *l_cons;
	} value;

	enum LispType type;
};

struct Cons {
	struct LispObj *car;
	struct LispObj *cdr;
};
